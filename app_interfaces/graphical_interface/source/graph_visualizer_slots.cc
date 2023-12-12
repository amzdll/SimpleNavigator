#include <QBrush>
#include <QPainter>
#include <QPen>

#include "../ui/ui_graph_visualizer.h"
#include "graph_visualizer.h"

GraphVisualizer::GraphVisualizer(QWidget *parent)
    : QWidget(parent), ui(new Ui::GraphVisualizer) {
  ui->setupUi(this);
  setAutoFillBackground(true);
  setPalette(QPalette(QColor(0, 0, 0)));
}

GraphVisualizer::~GraphVisualizer() { delete ui; }

void GraphVisualizer::OpenGraph() {
  QString file_name = QFileDialog::getOpenFileName(
      nullptr, "Выберите файл", "../../../materials/examples", "*.txt");
  if (!file_name.isEmpty()) {
    if (graph_.LoadGraphFromFile(file_name.toStdString())) {
      temporaryPixmap = {};
      adjacency_matrix_ = graph_.GetGraph();
      InitGraph();
      ApplyForces();
      CenterGraph();
      DrawGraph();
      update();
    }
  }
}

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

void GraphVisualizer::DFS() {
  auto dfc_vertices = s21::GraphAlgorithms::DepthFirstSearch(graph_, 3);
  DrawVertices();
  QTimer::singleShot(500, this, [=]() {
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

void GraphVisualizer::ApplyForces() {
  for (int i = 0; i < 500; ++i) {
    auto spring_forces = SpringForce();
    auto repulsion_force = RepulsionForce();
    for (int index = 0; index < vertices_.size(); ++index) {
      vertices_[index].second +=
          spring_forces[index].second + repulsion_force[index].second;
    }
  }
}

QVector<QPair<float, QVector2D>> GraphVisualizer::RepulsionForce() {
  const qreal k = -0.5;
  QVector<QPair<float, QVector2D>> forces(vertices_.size(), {});
  for (int i = 1; i < vertices_.size(); ++i) {
    QVector2D force(0, 0);
    for (int j = 1; j < vertices_.size(); ++j) {
      if (i != j) {
        QVector2D delta = vertices_[j].second - vertices_[i].second;
        qreal distance = delta.length();
        force += delta.normalized() * (1.0 / distance) * k * distance;
      }
    }
    forces[i].second += force;
  }
  return forces;
}

QVector<QPair<float, QVector2D>> GraphVisualizer::SpringForce() {
  const qreal k = 0.3;
  QVector<QPair<float, QVector2D>> forces(vertices_.size(), {});
    for (int i = 1; i < vertices_.size(); ++i) {
      for (int j = i + 1; j < vertices_.size(); ++j) {
        if (adjacency_matrix_[i][j] != 0) {
          QVector2D delta = vertices_[j].second - vertices_[i].second;
          qreal distance = delta.length();
          QVector2D force =
              delta.normalized() * (distance - adjacency_matrix_[i][j] * 10) *
              k;
          forces[i].second += force;
          forces[j].second -= force;
        }
      }
    }
  return forces;
}

void GraphVisualizer::CenterGraph() {
  int windowWidth = width();
  int windowHeight = height();

  qreal minX = std::numeric_limits<qreal>::max();
  qreal minY = std::numeric_limits<qreal>::max();
  qreal maxX = std::numeric_limits<qreal>::min();
  qreal maxY = std::numeric_limits<qreal>::min();

  for (int i = 1; i < vertices_.size(); ++i) {
    minX = qMin(minX, vertices_[i].second.x());
    minY = qMin(minY, vertices_[i].second.y());
    maxX = qMax(maxX, vertices_[i].second.x());
    maxY = qMax(maxY, vertices_[i].second.y());
  }

  qDebug() << minX << vertices_[3];

  qreal graphWidth = maxX - minX;
  qreal graphHeight = maxY - minY;

  // Определение масштаба для увеличения графа до 80% от окна
  qreal scale =
      qMin(0.8 * windowWidth / graphWidth, 0.8 * windowHeight / graphHeight);

  // Определение смещения для центрирования
  qreal offsetX = (windowWidth - scale * graphWidth) / 2;
  qreal offsetY = (windowHeight - scale * graphHeight) / 2;

  for (auto &position : vertices_) {
    // Масштабирование и центрирование каждой позиции узла
    position.second.setX((position.second.x() - minX) * scale + offsetX);
    position.second.setY((position.second.y() - minY) * scale + offsetY);
  }

  // Обновление отображения
  update();
}
