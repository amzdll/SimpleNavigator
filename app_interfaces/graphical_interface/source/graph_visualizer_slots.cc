#include "../ui/ui_graph_visualizer.h"
#include "graph_visualizer.h"

GraphVisualizer::GraphVisualizer(QWidget *parent)
    : QWidget(parent), ui(new Ui::GraphVisualizer) {
  ui->setupUi(this);
  setAutoFillBackground(true);
  setPalette(QPalette(QColor(0, 0, 0)));
}

GraphVisualizer::~GraphVisualizer() { delete ui; }

void GraphVisualizer::InitGraph() {
  vertices_ = {};
  edge_weights_ = {};
  int rows = adjacency_matrix_.GetRows();
  int cols = adjacency_matrix_.GetCols();
  vertices_.resize(rows);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 850);

  for (int row = 1; row < rows; ++row) {
    vertices_[row].second = QVector2D(dis(gen), dis(gen));
    for (int col = 1; col < cols; ++col) {
      if (adjacency_matrix_[row][col] != 0) {
        edge_weights_[QPair<int, int>(row, col)] = adjacency_matrix_[row][col];
      }
    }
  }
}

void GraphVisualizer::OpenGraph() {
  QString file_name = QFileDialog::getOpenFileName(
      nullptr, "Выберите файл", "../../../materials/examples", "*.txt");
  if (!file_name.isEmpty()) {
    if (graph_.LoadGraphFromFile(file_name.toStdString())) {
      adjacency_matrix_ = graph_.GetGraph();
      pixmap_ = {};
      InitGraph();
      vertices_ = Helpers::ApplyForces(vertices_, adjacency_matrix_);
      vertices_ = Helpers::CenterGraph(vertices_, width(), height());
      DrawGraph();
    }
  }
}

void GraphVisualizer::DFS(float start_vertex) {
  auto dfc_vertices =
      s21::GraphAlgorithms::DepthFirstSearch(graph_, start_vertex);
  DrawVertices();
  QTimer::singleShot(300, this, [=]() {
    for (auto vertex : dfc_vertices) {
      DrawVertex(vertex, Qt::white, Qt::red);
      QEventLoop loop;
      QTimer::singleShot(300, &loop, &QEventLoop::quit);
      loop.exec();
    }
  });
}

void GraphVisualizer::BFS(float start_vertex) {
  auto bfs_vertices =
      s21::GraphAlgorithms::BreadthFirstSearch(graph_, start_vertex);
  DrawVertices();
  QTimer::singleShot(300, this, [=]() {
    for (auto vertex : bfs_vertices) {
      DrawVertex(vertex, Qt::white, Qt::red);
      QEventLoop loop;
      QTimer::singleShot(300, &loop, &QEventLoop::quit);
      loop.exec();
    }
  });
}

void GraphVisualizer::GetShortestPathBetweenVertices(float start_vertex,
                                                     float end_vertex) {}

void GraphVisualizer::TSM() {
  pixmap_.fill(Qt::black);
  s21::GraphAlgorithms::TsmResult result =
      s21::GraphAlgorithms::SolveTravelingSalesmanProblem(graph_);
  QPainter painter(&pixmap_);
  QPen pen(Qt::white);
  for (int i = 1; i < adjacency_matrix_.GetRows(); ++i) {
    for (int j = i + 1; j < adjacency_matrix_.GetRows(); ++j) {
      pen.setWidth(int(result.pheromones[i][j] + 1));
      painter.setPen(pen);
      if (adjacency_matrix_[i][j] != 0) {
        painter.drawLine(vertices_[i].second.toPointF(),
                         vertices_[j].second.toPointF());
      }
    }
  }
  painter.end();
  DrawVertices();
  DrawEdgesValue();
}

void GraphVisualizer::Redraw() {
  pixmap_ = {};
  InitGraph();
  vertices_ = Helpers::ApplyForces(vertices_, adjacency_matrix_);
  vertices_ = Helpers::CenterGraph(vertices_, height(), width());
  DrawGraph();
}