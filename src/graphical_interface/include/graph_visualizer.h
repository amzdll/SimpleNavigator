#ifndef GRAPH_VISUALIZER_H
#define GRAPH_VISUALIZER_H

#include <QApplication>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPointF>
#include <QTimer>
#include <QVector>
#include <QWidget>
#include <cmath>

namespace Ui {
class GraphVisualizer;
}

class GraphVisualizer : public QWidget {
  Q_OBJECT

 public:
  explicit GraphVisualizer(QWidget *parent = nullptr);
  ~GraphVisualizer();

 private:
  Ui::GraphVisualizer *ui;
};

#endif  // GRAPH_VISUALIZER_H
