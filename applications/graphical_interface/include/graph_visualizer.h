#ifndef GRAPH_VISUALIZER_H
#define GRAPH_VISUALIZER_H

#include <QApplication>
#include <QPainter>
#include <QPointF>
#include <QTimer>
#include <QVector2D>
#include <QVector>
#include <QWidget>
#include <algorithm>

#include "helpers.h"
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

  void OpenGraph(const s21::Graph& graph);
  // void Spintree
  void DrawPath(const std::vector<float> &path);
  void TSM(const s21::GraphAlgorithms::TsmResult& tsm_result);
 public slots:

  void Redraw(const s21::Graph& graph);

 protected:
  //todo: mb to private?



  void paintEvent(QPaintEvent *event) override;

 private:
  struct style_settings {
    QImage town_icon;
    QString background_path;
  };
  s21::Graph graph_{};
  QPixmap pixmap_{};
  s21::matrix<float> adjacency_matrix_{};
  QMap<float, QVector2D> vertices_;
  QMap<QPair<int, int>, float> edge_weights_;
  QTimer timer_;
  style_settings style_settings_{};

  Ui::GraphVisualizer *ui;

  void InitGraph();
  void ConfigureStyleSettings();
  // todo: void ChangeWeightsGraph();
  void DrawGraph();
  void DrawEdges();
  void DrawVertices();
  void DrawEdgesValue();
  void DrawVertex(float vertex, Qt::GlobalColor text_color,
                  Qt::GlobalColor vertex_color);
  void RecolorVertexImage(const QColor& newColor);

};

#endif  // GRAPH_VISUALIZER_H