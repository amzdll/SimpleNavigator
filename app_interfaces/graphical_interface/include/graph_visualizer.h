#ifndef GRAPH_VISUALIZER_H
#define GRAPH_VISUALIZER_H

#include <QtGui/qpainterpath.h>

#include <QApplication>
#include <QFileDialog>
#include <QPainter>
#include <QPointF>
#include <QVector2D>
#include <QVector>
#include <QWidget>
#include <algorithm>

#include "list"
#include "random"
#include "s21_graph.h"
#include "s21_graph_algorithms.h"

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
  void DFC();

 protected:
  void paintEvent(QPaintEvent* event) override;
  QTimer* colorAnimationTimer;
  int currentStep;


 private:
  QPixmap temporaryPixmap;  // Временное хранилище для рисунка
  s21::Graph graph_;
  s21::matrix<float> adjacency_matrix_{};
  QVector<QVector2D> positions_;
  QMap<QPair<int, int>, double> edge_weights_;

//  QPainter painter_;

  Ui::GraphVisualizer* ui;

  void InitGraph();

  void DrawEdges();
  void DrawVertices();
  void DrawEdgesValue();

  //  void CalculateSpringForces(QVector<QPointF>& spring_forces);
  void ApplyForces();

  QVector<QVector2D> RepulsionForce();
  QVector<QVector2D> SpringForce();
  void CenterGraph();
};

#endif  // GRAPH_VISUALIZER_H