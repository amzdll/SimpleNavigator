#include "../ui/ui_graph_visualizer.h"
#include "graph_visualizer.h"

GraphVisualizer::GraphVisualizer(QWidget *parent)
    : QWidget(parent), ui(new Ui::GraphVisualizer) {
  ui->setupUi(this);
  ConfigureStyleSettings();
}

void GraphVisualizer::ConfigureStyleSettings() {
  setAutoFillBackground(true);
  setPalette(QPalette(QColor(0, 0, 0)));
  style_settings_.background_path = ":resources/img/map_background.png";
  style_settings_.town_icon = QImage(":resources/img/town_icon.png").scaled(50, 50, Qt::KeepAspectRatio);
  pixmap_ = QPixmap(style_settings_.background_path);
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
    vertices_[row].first = adjacency_matrix_[0][row];
    vertices_[row].second = QVector2D(dis(gen), dis(gen));
    for (int col = 1; col < cols; ++col) {
      if (adjacency_matrix_[row][col] != 0) {
        edge_weights_[QPair<int, int>(row, col)] = adjacency_matrix_[row][col];
      }
    }
  }
}

void GraphVisualizer::OpenGraph(const s21::Graph& graph) {
  adjacency_matrix_ = graph.GetGraph();
  pixmap_ = {};
  InitGraph();
  vertices_ = Helpers::ApplyForces(vertices_, graph.GetGraph());
  vertices_ = Helpers::CenterGraph(vertices_, width(), height());
  RecolorVertexImage(Qt::green);
  DrawGraph();
}

void GraphVisualizer::DrawPath(const std::vector<float> &path) {
  DrawVertices();
  RecolorVertexImage(Qt::darkGreen);
  QTimer::singleShot(300, this, [=]() {
    for (auto vertex : path) {
      DrawVertex(vertex, Qt::white, Qt::red);
      QEventLoop loop;
      QTimer::singleShot(300, &loop, &QEventLoop::quit);
      loop.exec();
    }
  });
}

void GraphVisualizer::TSM(const s21::GraphAlgorithms::TsmResult &tsm_result) {
  pixmap_ = QPixmap(style_settings_.background_path);
  QPainter painter(&pixmap_);
  QPen pen(Qt::green, 2, Qt::DashLine);
  for (int i = 1; i < tsm_result.pheromones.GetRows(); ++i) {
    for (int j = i + 1; j < tsm_result.pheromones.GetRows(); ++j) {
      pen.setWidth(int(tsm_result.pheromones[i][j] + 1));
      painter.setPen(pen);
      if (tsm_result.pheromones[i][j] != 0) {
        painter.drawLine(vertices_[i].second.toPointF(),
                         vertices_[j].second.toPointF());
      }
    }
  }
  painter.end();
  DrawVertices();
  DrawEdgesValue();
}

void GraphVisualizer::Redraw(const s21::Graph& graph) {
  pixmap_ = {};
  InitGraph();
  vertices_ = Helpers::ApplyForces(vertices_, graph.GetGraph());
  vertices_ = Helpers::CenterGraph(vertices_, height(), width());
  DrawGraph();
}