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
      vertices_ = ForcesHelpers::ApplyForces(vertices_, adjacency_matrix_);
      vertices_ = ForcesHelpers::CenterGraph(width(), height(), vertices_);
      DrawGraph();
    }
  }
}

void GraphVisualizer::DFS() {
  auto dfc_vertices = s21::GraphAlgorithms::DepthFirstSearch(graph_, 3);
  DrawVertices();
  QTimer::singleShot(100, this, [=]() {
    for (auto vertex : dfc_vertices) {
      DrawVertex(vertex, Qt::white, Qt::red);
      QEventLoop loop;
      QTimer::singleShot(500, &loop, &QEventLoop::quit);
      loop.exec();
    }
  });
}

void GraphVisualizer::BFS() {
  auto bfs_vertices = s21::GraphAlgorithms::BreadthFirstSearch(graph_, 3);
  DrawVertices();
  QTimer::singleShot(500, this, [=]() {
    for (auto vertex : bfs_vertices) {
      DrawVertex(vertex, Qt::white, Qt::red);
      QEventLoop loop;
      QTimer::singleShot(500, &loop, &QEventLoop::quit);
      loop.exec();
    }
  });
}