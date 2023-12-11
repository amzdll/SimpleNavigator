#include "graph_visualizer.h"

#include <QBrush>
#include <QPainter>
#include <QPen>

#include "../ui/ui_graph_visualizer.h"

GraphVisualizer::GraphVisualizer(QWidget* parent)
    : QWidget(parent), ui(new Ui::GraphVisualizer) {
  ui->setupUi(this);
  setAutoFillBackground(true);
  setPalette(QPalette(QColor(0, 0, 0)));
}

GraphVisualizer::~GraphVisualizer() { delete ui; }

void GraphVisualizer::OpenGraph() {
  QString file_name = QFileDialog::getOpenFileName(
      nullptr, "Выберите файл", "../../../../materials/examples", "*.txt");
  if (!file_name.isEmpty()) {
    if (graph_.LoadGraphFromFile(file_name.toStdString())) {
      adjacency_matrix_ = graph_.GetGraph();
      InitGraph();
      ApplyForces();
      CenterGraph();
      update();
    }
  }
}

void GraphVisualizer::DFC() {
  auto dfc_list = s21::GraphAlgorithms::DepthFirstSearch(graph_, 3);
  for (auto i : dfc_list) {
    qDebug() << i;
  }

  temporaryPixmap = QPixmap(size());  // Инициализация временного хранилища
  temporaryPixmap.fill(Qt::transparent);  // Заполнение прозрачным фоном

  QPainter painter(&temporaryPixmap);
  painter.setPen(QPen(Qt::red));

  for (int i = 1; i < adjacency_matrix_.GetRows(); ++i) {
    for (int j = i + 1; j < adjacency_matrix_.GetRows(); ++j) {
      if (adjacency_matrix_[i][j] != 0) {
        painter.drawLine(positions_[i].toPointF(), positions_[j].toPointF());
      }
    }
  }

  update();
}

void GraphVisualizer::paintEvent(QPaintEvent* event) {
  Q_UNUSED(event)
  QPainter painter(this);
  if (!temporaryPixmap.isNull()) {
    painter.drawPixmap(0, 0, temporaryPixmap);
  } else {
    DrawEdges();
    DrawVertices();
    DrawEdgesValue();
  }
}

void GraphVisualizer::InitGraph() {

  positions_ = {};
  edge_weights_ = {};
  int rows = adjacency_matrix_.GetRows();
  int cols = adjacency_matrix_.GetCols();
  positions_.resize(rows);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 850);

  for (int row = 1; row < rows; ++row) {
    positions_[row] = QVector2D(dis(gen), dis(gen));
    for (int col = 1; col < cols; ++col) {
      if (adjacency_matrix_[row][col] != 0) {
        edge_weights_[QPair<int, int>(row, col)] = adjacency_matrix_[row][col];
      }
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

void GraphVisualizer::DrawEdgesValue() {
  QPainter painter(this);
  QFont font;
  font.setBold(true);
  font.setPointSize(14);
  painter.setFont(font);
  painter.setPen(QPen(Qt::green, 2, Qt::SolidLine));
  painter.setOpacity(1.0);
  QFontMetricsF fontMetrics(font);

  for (auto it = edge_weights_.cbegin(); it != edge_weights_.cend(); ++it) {
    if (it.value() != 0) {
      const QPair<int, int>& vertices = it.key();
      int vertex1 = vertices.first;
      int vertex2 = vertices.second;
      QPointF center =
          (positions_[vertex1].toPointF() + positions_[vertex2].toPointF()) / 2;
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
    for (int index = 0; index < positions_.size(); ++index) {
      positions_[index] += spring_forces[index] + repulsion_force[index];
    }
  }
}

QVector<QVector2D> GraphVisualizer::RepulsionForce() {
  const qreal k = -0.1;  // Коэффициент силы отталкивания
  QVector<QVector2D> forces(positions_.size());
  for (int i = 1; i < positions_.size(); ++i) {
    QVector2D force(0, 0);
    for (int j = 1; j < positions_.size(); ++j) {
      if (i != j) {
        QVector2D delta = positions_[j] - positions_[i];
        qreal distance = delta.length();
        force += adjacency_matrix_[i][j] * 10 * delta.normalized() *
                 (1.0 / distance) * k * distance;
      }
    }
    forces[i] += force;
  }
  return forces;
}

QVector<QVector2D> GraphVisualizer::SpringForce() {
  const qreal k = 0.1;  // Коэффициент упругости пружины
  QVector<QVector2D> forces(positions_.size(), QVector2D(0, 0));
  for (int i = 1; i < positions_.size(); ++i) {
    for (int j = i + 1; j < positions_.size(); ++j) {
      QVector2D delta = positions_[j] - positions_[i];
      qreal distance = delta.length();
      QVector2D force =
          delta.normalized() * (distance - adjacency_matrix_[i][j] * 10) * k;
      forces[i] += force;
      forces[j] -= force;
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

  for (int i = 1; i < positions_.size(); ++i) {
    minX = qMin(minX, positions_[i].x());
    minY = qMin(minY, positions_[i].y());
    maxX = qMax(maxX, positions_[i].x());
    maxY = qMax(maxY, positions_[i].y());
  }

  qDebug() << minX << positions_[3];

  qreal graphWidth = maxX - minX;
  qreal graphHeight = maxY - minY;

  // Определение масштаба для увеличения графа до 80% от окна
  qreal scale =
      qMin(0.8 * windowWidth / graphWidth, 0.8 * windowHeight / graphHeight);

  // Определение смещения для центрирования
  qreal offsetX = (windowWidth - scale * graphWidth) / 2;
  qreal offsetY = (windowHeight - scale * graphHeight) / 2;

  for (auto& position : positions_) {
    // Масштабирование и центрирование каждой позиции узла
    position.setX((position.x() - minX) * scale + offsetX);
    position.setY((position.y() - minY) * scale + offsetY);
  }

  // Обновление отображения
  update();
}

