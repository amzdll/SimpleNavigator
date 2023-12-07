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
#include <QVector2D>
#include <QVector>
#include <QWidget>
#include <cmath>

#include "random"
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

 protected:
  void paintEvent(QPaintEvent* event) override;

 private:
  s21::Graph graph_;
  s21::matrix<float> adjacency_matrix_{};

  QVector<QVector2D> positions_;
  QMap<QPair<int, int>, double> edge_weights_;

  Ui::GraphVisualizer* ui;

  void InitGraph();

  void DrawEdges();
  void DrawVertices();

  //  void CalculateSpringForces(QVector<QPointF>& spring_forces);
  void applyForces();
  void centerGraph();
};

#endif  // GRAPH_VISUALIZER_H
