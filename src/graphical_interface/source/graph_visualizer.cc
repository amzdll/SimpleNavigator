#include "../include/graph_visualizer.h"

#include "../ui/ui_graph_visualizer.h"

GraphVisualizer::GraphVisualizer(QWidget *parent)
    : QWidget(parent), ui(new Ui::GraphVisualizer) {
  ui->setupUi(this);

  scene_ = new QGraphicsScene(this);
  scene_->setSceneRect(0, 0, 500, 500);
  scene_->setBackgroundBrush(QColor(0, 0, 0));
  view_ = new QGraphicsView(scene_);
  layout_ = new QVBoxLayout(this);
  layout_->addWidget(view_);
  setLayout(layout_);
  QRectF ellipseRect(0, 0, 100, 100);
  QPen ellipsePen(Qt::black);
  QBrush ellipseBrush(Qt::red);
  scene_->addEllipse(ellipseRect, ellipsePen, ellipseBrush);

}

GraphVisualizer::~GraphVisualizer() { delete ui; }
