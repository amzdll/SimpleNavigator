#ifndef GRAPH_VISUALIZER_H
#define GRAPH_VISUALIZER_H

#include <QApplication>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPointF>
#include <QTimer>
#include <QVBoxLayout>
#include <QVector>
#include <QWidget>
#include <cmath>

#include "s21_graph.h"

namespace Ui {
class GraphVisualizer;
}

class GraphVisualizer : public QWidget {
  Q_OBJECT

 public:
  explicit GraphVisualizer(QWidget* parent = nullptr);
  ~GraphVisualizer();

 public slots:
  void OpenGraph();

 private:
  s21::Graph graph_;
  s21::matrix<float> adjacency_matrix_{};

  QGraphicsScene* scene_;
  QGraphicsView* view_;
  QVBoxLayout* layout_;

  QList<QGraphicsEllipseItem*> vertices_;
  QList<QGraphicsLineItem*> edges_;

  Ui::GraphVisualizer* ui;

  void DrawGraph();
};

#endif  // GRAPH_VISUALIZER_H
