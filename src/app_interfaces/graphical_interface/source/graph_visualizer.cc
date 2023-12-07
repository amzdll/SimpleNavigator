#include "graph_visualizer.h"

#include <QBrush>
#include <QPainter>
#include <QPen>

#include "../ui/ui_graph_visualizer.h"

GraphVisualizer::GraphVisualizer(QWidget* parent)
    : QWidget(parent), ui(new Ui::GraphVisualizer) {
  ui->setupUi(this);
  setAutoFillBackground(true);  // Включаем заливку фона
  setPalette(QPalette(QColor(0, 0, 0)));
}

GraphVisualizer::~GraphVisualizer() { delete ui; }

void GraphVisualizer::OpenGraph() {
  graph_.LoadGraphFromFile(
      "/Users/glenpoin/W/Projects/Algorithms/SimpleNavigator/materials/"
      "examples/graph_1.txt");
  adjacency_matrix_ = graph_.GetGraph();
  qDebug() << adjacency_matrix_.GetRows();
  InitGraph();
  ApplyForces();
  CenterGraph();
  update();
}

void GraphVisualizer::paintEvent(QPaintEvent* event) {
  Q_UNUSED(event)

  QPainter painter(this);

  DrawEdges(painter);
  DrawVertices(painter);
  DrawEdgesValue(painter);
}

void GraphVisualizer::InitGraph() {
  int rows = adjacency_matrix_.GetRows();
  int cols = adjacency_matrix_.GetCols();
  positions_.resize(rows);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 820);
  for (int row = 1; row < rows; ++row) {
    positions_[row] = QVector2D(dis(gen), dis(gen));
    gradient_.push_back(QVector2D(0.0, 0.0));
    for (int col = 1; col < cols; ++col) {
      edge_weights_[qMakePair(row, col)] = adjacency_matrix_[row][col];
    }
  }
}

void GraphVisualizer::DrawEdges(QPainter& painter) {
  painter.setPen(QPen(Qt::white));
  for (int i = 1; i < adjacency_matrix_.GetRows(); ++i) {
    for (int j = i + 1; j < adjacency_matrix_.GetRows(); ++j) {
      if (adjacency_matrix_[i][j] != 0) {
        painter.drawLine(positions_[i].toPointF(), positions_[j].toPointF());
      }
    }
  }
}

void GraphVisualizer::DrawVertices(QPainter& painter) {
  painter.setPen(QPen(Qt::black));
  painter.setBrush(QBrush(Qt::white));
  for (int i = 1; i < adjacency_matrix_.GetRows(); ++i) {
    painter.drawEllipse(positions_[i].toPointF(), 20, 20);
    QRectF textRect =
        QRectF(positions_[i].x() - 10, positions_[i].y() - 10, 20, 20);
    painter.drawText(textRect, Qt::AlignCenter,
                     QString::number(adjacency_matrix_[0][i]));
  }
}

void GraphVisualizer::DrawEdgesValue(QPainter& painter) {
  QFont font = painter.font();
  font.setWeight(QFont::Bold);
  painter.setFont(font);
  painter.setPen(QPen(Qt::green, 2, Qt::SolidLine));
  painter.setBrush(QBrush(Qt::black));
  for (auto it = edge_weights_.cbegin(); it != edge_weights_.cend(); ++it) {
    if (it.value() != 0) {
      const QPair<int, int>& vertices = it.key();
      int vertex1 = vertices.first;
      int vertex2 = vertices.second;
      QPointF center =
          (positions_[vertex1].toPointF() + positions_[vertex2].toPointF()) / 2;
      painter.drawText(center, QString::number(it.value()));
    }
  }
}

// void GraphVisualizer::ApplyForces() {
//   float spring_constant = 0.01;
//   float repulsion_constant = 2;
//   float damping_factor = 1;
//   int iterations = 500;
//
//   for (int iter = 0; iter < iterations; ++iter) {
//     for (auto it = edge_weights_.begin(); it != edge_weights_.end(); ++it) {
//       int node1 = it.key().first;
//       int node2 = it.key().second;
//       float dx = positions_[node2].x() - positions_[node1].x();
//       float dy = positions_[node2].y() - positions_[node1].y();
//       float distance = std::sqrt(dx * dx + dy * dy);
//       float spring_force = spring_constant * (distance - it.value());
//       positions_[node1] +=
//           QVector2D(dx, dy).normalized() * spring_force * damping_factor;
//       positions_[node2] -=
//           QVector2D(dx, dy).normalized() * spring_force * damping_factor;
//     }
//     for (int i = 0; i < positions_.size(); ++i) {
//       for (int j = i + 1; j < positions_.size(); ++j) {
//         QVector2D delta = positions_[j] - positions_[i];
//         float distance = delta.length();
//         float repulsion_force = repulsion_constant / (distance * distance);
//         positions_[i] -= delta.normalized() * repulsion_force *
//         damping_factor; positions_[j] += delta.normalized() * repulsion_force
//         * damping_factor;
//       }
//     }
//   }
// }

QVector2D GraphVisualizer::computeGradient(int vertex) {
  const double spring_constant = 1.0;  // Коэффициент пружины
  const double distance_limit = 1.0;  // Предел расстояния между вершинами
  const double epsilon = 1e-5;  // Малая константа для избежания деления на ноль

  gradient_.clear();
  gradient_.resize(positions_.size(), QVector2D(0.0, 0.0));

  for (int i = 0; i < positions_.size(); ++i) {
    for (int j = i + 1; j < positions_.size(); ++j) {
      QVector2D direction = positions_[i] - positions_[j];
      double distance = direction.length();
      double weight = 0.0;
      auto edge_weight_it = edge_weights_.find(qMakePair(i, j));
      if (edge_weight_it != edge_weights_.end()) {
        weight = edge_weight_it.value();
      }
      QVector2D force = weight * (distance - distance_limit) * direction /
                        (distance + epsilon);
      gradient_[i] += force;
      gradient_[j] -= force;
    }
  }

  for (auto& grad : gradient_) {
    grad *= spring_constant;
  }
}

double GraphVisualizer::computePotentialEnergy() {
  const double spring_constant = 1.0;
  const double distance_limit = 1.0;
  const double epsilon = 1e-5;
  double energy = 0.0;
  for (int i = 0; i < positions_.size(); ++i) {
    for (int j = i + 1; j < positions_.size(); ++j) {
      double distance = QVector2D(positions_[i] - positions_[j]).length();
      double weight = 0.0;
      auto edge_weight_it = edge_weights_.find(qMakePair(i, j));
      if (edge_weight_it != edge_weights_.end()) {
        weight = edge_weight_it.value();
      }
      energy +=
          weight * pow(distance - distance_limit, 2) / (distance + epsilon);
    }
  }

  return 0.5 * spring_constant *
         energy;  // Множитель 0.5 добавляется для удобства
}

void GraphVisualizer::ApplyForces() {
  const double repulsionFactor = 20;
  const double attractionFactor = 0.005;
  int numVertices = positions_.size();

  for (int fatix = 0; fatix < 1000; ++fatix) {
    QVector<QVector2D> forces(numVertices, QVector2D(0.0, 0.0));
    for (int i = 1; i < numVertices; ++i) {
      for (int j = 1; j < numVertices; ++j) {
        if (i != j) {
          QVector2D direction = positions_[i] - positions_[j];
          double distance =
              qMax(direction.length(), 1.0);  // Избегаем деление на 0
          QVector2D force = repulsionFactor * direction / (distance * distance);
          forces[i] += force;
        }
      }
    }

    for (int i = 1; i < numVertices; ++i) {
      for (int j = 1; j < numVertices; ++j) {
        if (i != j && adjacency_matrix_[i][j] > 0) {
          QVector2D direction = positions_[j] - positions_[i];
          double distance =
              qMax(direction.length(), 1.0);  // Избегаем деление на 0
          QVector2D force =
              (attractionFactor * adjacency_matrix_[i][j] * direction) /
              distance;
          forces[i] += force;
        }
      }
    }

    for (int i = 1; i < numVertices; ++i) {
      positions_[i] += forces[i];
    }
  }
}

void GraphVisualizer::CenterGraph() {}
