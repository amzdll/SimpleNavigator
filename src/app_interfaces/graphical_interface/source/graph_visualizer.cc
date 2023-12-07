#include "graph_visualizer.h"

#include <QBrush>
#include <QPainter>
#include <QPen>

#include "../ui/ui_graph_visualizer.h"
#include "graph_visualizer.h"

GraphVisualizer::GraphVisualizer(QWidget* parent)
    : QWidget(parent), ui(new Ui::GraphVisualizer) {
  ui->setupUi(this);
  setAutoFillBackground(true);  // Включаем заливку фона
  setPalette(QPalette(QColor(0, 0, 0)));
}

GraphVisualizer::~GraphVisualizer() { delete ui; }

void GraphVisualizer::OpenGraph() {
  graph_.LoadGraphFromFile(
      "/home/freiqq/Projects/Algorithms/SimpleNavigator/materials/examples/"
      "graph_1.txt");
  adjacency_matrix_ = graph_.GetGraph();
  applyForces();
  InitGraph();

  centerGraph();
  update();  // вызов метода update() для обновления виджета
}

void GraphVisualizer::paintEvent(QPaintEvent* event) {
  Q_UNUSED(event)
  QPainter painter;
  painter.setRenderHint(QPainter::Antialiasing);

  DrawEdges();
  DrawVertices();
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
    for (int col = 1; col < cols; ++col) {
      edge_weights_[qMakePair(row, col)] = adjacency_matrix_[row][col];
    }
  }
}

void GraphVisualizer::DrawEdges() {
  QPainter painter(this);
  painter.setPen(QPen(Qt::white));
  for (int i = 1; i < adjacency_matrix_.GetRows(); ++i) {
    for (int j = i + 1; j < adjacency_matrix_.GetRows(); ++j) {
      if (adjacency_matrix_[i][j] != 0) {
        painter.drawLine(positions_[i].toPointF(), positions_[j].toPointF());
      }
    }
  }

  QFont font = painter.font();
  font.setWeight(QFont::Bold);
  painter.setFont(font);
  painter.setPen(QPen(Qt::green, 2, Qt::SolidLine));  // 2 - толщина черной обводки, Qt::SolidLine - тип линии



  for (auto it = edge_weights_.constBegin(); it != edge_weights_.constEnd();
       ++it) {
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

void GraphVisualizer::DrawVertices() {
  QPainter painter(this);
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

void GraphVisualizer::applyForces() {
  float spring_constant = 0.01;
  float repulsion_constant = 2;
  float damping_factor =1;
  int iterations = 500;


  for (int iter = 0; iter < iterations; ++iter) {
//    damping_factor = 1.0 - damping_factor;
    for (auto it = edge_weights_.begin(); it != edge_weights_.end(); ++it) {
      int node1 = it.key().first;
      int node2 = it.key().second;

      float dx = positions_[node2].x() - positions_[node1].x();
      float dy = positions_[node2].y() - positions_[node1].y();
      float distance = std::sqrt(dx * dx + dy * dy);

      float spring_force = spring_constant * (distance - it.value());

      positions_[node1] += QVector2D(dx, dy).normalized() * spring_force * damping_factor;
      positions_[node2] -= QVector2D(dx, dy).normalized() * spring_force * damping_factor;
    }

    for (int i = 0; i < positions_.size(); ++i) {
      for (int j = i + 1; j < positions_.size(); ++j) {
        QVector2D delta = positions_[j] - positions_[i];
        float distance = delta.length();

        // Учитываем вес ребра при вычислении силы отталкивания
        float repulsion_force = repulsion_constant / (distance * distance);

        positions_[i] -= delta.normalized() * repulsion_force * damping_factor;
        positions_[j] += delta.normalized() * repulsion_force * damping_factor;
      }
    }
  }
}

void GraphVisualizer::centerGraph() {
  // Найти центр масс графа
  QVector2D centerOfMass(0.0, 0.0);
  for (const auto& position : positions_) {
    centerOfMass += position;
  }
  centerOfMass /= positions_.size();

  // Вычислить смещение
  QVector2D offset((400 - centerOfMass.x()) / 2, (400 - centerOfMass.y()) / 2);

  // Сместить все вершины
  for (auto& position : positions_) {
    position += offset;
  }
}
