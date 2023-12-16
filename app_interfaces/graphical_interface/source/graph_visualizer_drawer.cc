#include <QBrush>
#include <QPainter>
#include <QPen>

#include "../ui/ui_graph_visualizer.h"
#include "graph_visualizer.h"

void GraphVisualizer::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event)
  QPainter painter(this);
  painter.drawPixmap(0, 0, pixmap_);
}

void GraphVisualizer::DrawGraph() {
  pixmap_ = QPixmap(size());
  pixmap_.fill(Qt::transparent);

  DrawEdges();
  DrawVertices();
  DrawEdgesValue();
}

void GraphVisualizer::DrawVertices() {
  for (int row = 0, col = 1; col < adjacency_matrix_.GetCols(); ++col) {
    DrawVertex(adjacency_matrix_[row][col], Qt::black, Qt::white);
  }
}

void GraphVisualizer::DrawEdgesValue() {
  QPainter painter(&pixmap_);
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
      QPointF center = (vertices_[vertex1].second.toPointF() +
                        vertices_[vertex2].second.toPointF()) /
                       2;
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

void GraphVisualizer::DrawEdges() {
  QPainter painter(&pixmap_);
  painter.setPen(QPen(Qt::white, 2));
  for (int i = 1; i < adjacency_matrix_.GetRows(); ++i) {
    for (int j = i + 1; j < adjacency_matrix_.GetRows(); ++j) {
      if (adjacency_matrix_[i][j] != 0) {
        painter.drawLine(vertices_[i].second.toPointF(),
                         vertices_[j].second.toPointF());
      }
    }
  }
}

void GraphVisualizer::DrawVertex(float vertex, Qt::GlobalColor text_color,
                                 Qt::GlobalColor vertex_color) {
  QPainter painter(&pixmap_);
  painter.setPen(QPen(text_color));
  painter.setBrush(QBrush(vertex_color));
  painter.drawEllipse(vertices_[vertex].second.toPointF(), 20, 20);
  QRectF textRect = QRectF(vertices_[vertex].second.x() - 10,
                           vertices_[vertex].second.y() - 10, 20, 20);
  painter.drawText(textRect, Qt::AlignCenter, QString::number(vertex));
  update();
}

