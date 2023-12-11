#include "graph_visualizer.h"

#include <QBrush>
#include <QPainter>
#include <QPen>

#include "../ui/ui_graph_visualizer.h"

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

void GraphVisualizer::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event)
  QPainter painter(this);
  painter.drawPixmap(0, 0, temporaryPixmap);
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

void GraphVisualizer::DFC() {
  auto a = s21::GraphAlgorithms::DepthFirstSearch(graph_, 3);
  connect(&timer_, &QTimer::timeout, [this, &a]() {
    DrawDFC(a);
  });

  timer_.start(1000);
}

void GraphVisualizer::DrawDFC(std::list<float>& vertices) {
  if (!vertices.empty()) {
    qDebug() << "";
    QPainter painter(&temporaryPixmap);
    painter.setPen(QPen(Qt::red));
    painter.setBrush(QBrush(Qt::white));
    painter.drawEllipse(vertices_.front().second.toPointF(), 20, 20);
    QRectF textRect =
        QRectF(vertices_.front().second.x() - 10, vertices_.front().second.y() - 10, 20, 20);
    painter.drawText(textRect, Qt::AlignCenter, QString::number(vertices_.front().first));

    update();
  } else {
    timer_.stop();
  }
}

void GraphVisualizer::DrawGraph() {
  temporaryPixmap = QPixmap(size());
  temporaryPixmap.fill(Qt::transparent);

  DrawEdges();
  DrawVertices();
  DrawEdgesValue();
}

void GraphVisualizer::DrawEdges() {
  QPainter painter(&temporaryPixmap);
  painter.setPen(QPen(Qt::white));
  for (int i = 1; i < adjacency_matrix_.GetRows(); ++i) {
    for (int j = i + 1; j < adjacency_matrix_.GetRows(); ++j) {
      if (adjacency_matrix_[i][j] != 0) {
        painter.drawLine(vertices_[i].second.toPointF(), vertices_[j].second.toPointF());
      }
    }
  }
}

void GraphVisualizer::DrawVertices() {
  QPainter painter(&temporaryPixmap);
  painter.setPen(QPen(Qt::black));
  painter.setBrush(QBrush(Qt::white));
  for (int i = 1; i < adjacency_matrix_.GetRows(); ++i) {
    painter.drawEllipse(vertices_[i].second.toPointF(), 20, 20);
    QRectF textRect =
        QRectF(vertices_[i].second.x() - 10, vertices_[i].second.y() - 10, 20, 20);
    painter.drawText(textRect, Qt::AlignCenter,
                     QString::number(adjacency_matrix_[0][i]));
  }
}

void GraphVisualizer::DrawEdgesValue() {
  QPainter painter(&temporaryPixmap);
  QFont font;
  font.setBold(true);
  font.setPointSize(14);
  painter.setFont(font);
  painter.setPen(QPen(Qt::green, 2, Qt::SolidLine));
  painter.setOpacity(1.0);
  QFontMetricsF fontMetrics(font);

  for (auto it = edge_weights_.cbegin(); it != edge_weights_.cend(); ++it) {
    if (it.value() != 0) {
      const QPair<int, int> &vertices = it.key();
      int vertex1 = vertices.first;
      int vertex2 = vertices.second;
      QPointF center =
          (vertices_[vertex1].second.toPointF() + vertices_[vertex2].second.toPointF()) / 2;
      QPointF textPosition =
          center -
              QPointF(
                  fontMetrics.boundingRect(QString::number(it.value())).width() / 2,
                  fontMetrics.boundingRect(QString::number(it.value())).height() /
                      2);
      painter.drawText(textPosition, QString::number(it.value()));
    }
  }
}

void GraphVisualizer::ApplyForces() {
  for (int i = 0; i < 100; ++i) {
    auto spring_forces = SpringForce();
    auto repulsion_force = RepulsionForce();
    for (int index = 0; index < vertices_.size(); ++index) {
      vertices_[index].second += spring_forces[index].second + repulsion_force[index].second;
    }
  }
}

QVector<QPair<float, QVector2D>> GraphVisualizer::RepulsionForce() {
  const qreal k = -0.1;
  QVector<QPair<float, QVector2D>> forces(vertices_.size(), {});
  for (int i = 1; i < vertices_.size(); ++i) {
    QVector2D force(0, 0);
    for (int j = 1; j < vertices_.size(); ++j) {
      if (i != j) {
        QVector2D delta = vertices_[j].second - vertices_[i].second;
        qreal distance = delta.length();
        force += adjacency_matrix_[i][j] * 10 * delta.normalized() *
            (1.0 / distance) * k * distance;
      }
    }
    forces[i].second += force;
  }
  return forces;
}

QVector<QPair<float, QVector2D>> GraphVisualizer::SpringForce() {
  const qreal k = 0.1;
  QVector<QPair<float, QVector2D>> forces(vertices_.size(), {});
  for (int i = 1; i < vertices_.size(); ++i) {
    for (int j = i + 1; j < vertices_.size(); ++j) {
      QVector2D delta = vertices_[j].second - vertices_[i].second;
      qreal distance = delta.length();
      QVector2D force =
          delta.normalized() * (distance - adjacency_matrix_[i][j] * 10) * k;
      forces[i].second += force;
      forces[j].second -= force;
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
