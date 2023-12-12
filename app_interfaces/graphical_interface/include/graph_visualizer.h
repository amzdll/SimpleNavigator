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
#include <QTimer>
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
  explicit GraphVisualizer(QWidget *parent = nullptr);
  ~GraphVisualizer();

 public slots:
  void OpenGraph();
  void DFS();
  void BFS();

 protected:
  void paintEvent(QPaintEvent *event) override;

 private:
  QPixmap temporaryPixmap{};  // Временное хранилище для рисунка
  s21::Graph graph_;
  s21::matrix<float> adjacency_matrix_{};
  QVector<QPair<float, QVector2D>> vertices_;
  QMap<QPair<int, int>, double> edge_weights_;
  QTimer timer_;

  Ui::GraphVisualizer *ui;

  void InitGraph();

  void DrawEdges();
  void DrawVertices();
  void DrawEdgesValue();



  void ApplyForces();

  QVector<QPair<float, QVector2D>> RepulsionForce();
  QVector<QPair<float, QVector2D>> SpringForce();
  void CenterGraph();
  void DrawGraph();

 private slots:
//  void DrawDFS(float vertex);
//  void DrawBFS(std::list<float>& vertices);
  void DrawVertex(float vertex, Qt::GlobalColor text_color,
                  Qt::GlobalColor vertex_color);
};

#endif  // GRAPH_VISUALIZER_H