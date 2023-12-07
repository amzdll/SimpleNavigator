#ifndef GRAPH_VISUALIZER_H
#define GRAPH_VISUALIZER_H

#include <QApplication>
#include <QPointF>
#include <QVector2D>
#include <QVector>
#include <QWidget>

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
  QVector<QVector2D> gradient_;


  Ui::GraphVisualizer* ui;

  void InitGraph();

  void DrawEdges(QPainter& painter);
  void DrawVertices(QPainter& painter);
  void DrawEdgesValue(QPainter& painter);

  //  void CalculateSpringForces(QVector<QPointF>& spring_forces);
  void ApplyForces();
  void CenterGraph();
  QVector2D computeGradient(int vertex) ;
  double computePotentialEnergy() ;
};

#endif  // GRAPH_VISUALIZER_H