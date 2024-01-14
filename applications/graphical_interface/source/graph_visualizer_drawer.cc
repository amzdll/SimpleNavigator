#include <QBrush>
#include <QPainter>
#include <QPen>

#include "../ui/ui_graph_visualizer.h"
#include "graph_visualizer.h"

void GraphVisualizer::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event)
  QPainter painter(this);
  painter.drawPixmap(0, 0, pixmap_);
  painter.end();
}

void GraphVisualizer::DrawGraph() {
  pixmap_ = QPixmap(style_settings_.background_path);
  DrawEdges();
  DrawVertices();
  DrawEdgesValue();
}

void GraphVisualizer::DrawVertices() {
  // fix: just recolor img in folder
  RecolorVertexImage(Qt::green);
  for (auto vertex : vertices_.keys()) {
    DrawVertex(vertex, Qt::black, Qt::white);
  }
}

void GraphVisualizer::DrawEdgesValue() {
  QPainter painter(&pixmap_);
  QFont font;
  font.setBold(true);
  font.setPointSize(12);
  painter.setFont(font);
  painter.setPen(QPen(Qt::green, 2, Qt::SolidLine));
  painter.setOpacity(1.0);
  QFontMetricsF fontMetrics(font);

  for (auto itr = edge_weights_.cbegin(); itr != edge_weights_.cend(); ++itr) {
    if (itr.value() != 0) {
      const QPair<int, int> &vertices = itr.key();
      int vertex1 = vertices.first;
      int vertex2 = vertices.second;
      QPointF center = (vertices_[vertex1].toPointF() +
                        vertices_[vertex2].toPointF()) /
                       2;
      QPointF textPosition =
          center -
          QPointF(
              fontMetrics.boundingRect(QString::number(itr.value())).width() /
                  2,
              fontMetrics.boundingRect(QString::number(itr.value())).height() /
                  2);
      painter.drawText(textPosition, QString::number(itr.value()));
    }
  }
  painter.end();
}

void GraphVisualizer::DrawEdges() {
  QPainter painter(&pixmap_);
  painter.setPen(QPen(Qt::green, 2, Qt::DashLine));

  for (int i = 1; i < adjacency_matrix_.GetRows(); ++i) {
    for (int j = i + 1; j < adjacency_matrix_.GetRows(); ++j) {
      if (adjacency_matrix_[i][j] != 0) {
        painter.drawLine(vertices_[i].toPointF(),
                         vertices_[j].toPointF());
      }
    }
  }
  painter.end();
}

void GraphVisualizer::DrawVertex(float vertex, Qt::GlobalColor text_color,
                                 Qt::GlobalColor vertex_color) {
  QPainter painter(&pixmap_);
  QFont font;
  font.setBold(true);
  font.setPointSize(14);
  painter.setPen(QPen(Qt::green));
  painter.setFont(font);
  painter.setBrush(QBrush(vertex_color));

  QRectF position;
  position.setX(vertices_[vertex].toPointF().x() - 20);
  position.setY(vertices_[vertex].toPointF().y() - 30);
  painter.drawImage(position, style_settings_.town_icon);
  QRectF textRect = QRectF(vertices_[vertex].x() - 5,
                           vertices_[vertex].y() + 30, 20, 20);
  painter.drawText(textRect, Qt::AlignCenter, QString::number(vertex));
  painter.end();

  update();
}

void GraphVisualizer::RecolorVertexImage(const QColor &newColor) {
  for (int y = 0; y < style_settings_.town_icon.height(); ++y) {
    for (int x = 0; x < style_settings_.town_icon.width(); ++x) {
      QColor pixelColor = style_settings_.town_icon.pixelColor(x, y);
      if (pixelColor.alpha() > 0) {
        style_settings_.town_icon.setPixelColor(x, y, newColor);
      }
    }
  }
}