#ifndef GRAPH_VISUALIZER_H
#define GRAPH_VISUALIZER_H

#include <QApplication>
#include <QFileDialog>
#include <QPainter>
#include <QPointF>
#include <QTimer>
#include <QVector2D>
#include <QVector>
#include <QWidget>
#include <algorithm>

#include "helpers.h"
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
  void OpenGraph(s21::Graph graph);
  void DFS(float start_vertex);
  void BFS(float start_vertex);
  void GetShortestPathBetweenVertices(float start_vertex, float end_vertex);
  void GetShortestPathBetweenTwoVertices(const std::vector<float> &path);
  void GetShortestPathBetweenAllVertices();
  void TSM();

  void Redraw();

 protected:
  //todo: mb to private?
  void paintEvent(QPaintEvent *event) override;

 private:
  QPixmap pixmap_{};
  s21::Graph graph_;
  s21::matrix<float> adjacency_matrix_{};
  QVector<QPair<float, QVector2D>> vertices_;
  QMap<QPair<int, int>, float> edge_weights_;
  QTimer timer_;

  Ui::GraphVisualizer *ui;

  void InitGraph();

  // todo: void ChangeWeightsGraph();
  void DrawGraph();
  void DrawEdges();
  void DrawVertices();
  void DrawEdgesValue();
  void DrawVertex(float vertex, Qt::GlobalColor text_color,
                  Qt::GlobalColor vertex_color);
};

#endif  // GRAPH_VISUALIZER_H