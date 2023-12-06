#include "graph_visualizer.h"
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
}

GraphVisualizer::~GraphVisualizer() { delete ui; }

void GraphVisualizer::OpenGraph() {
  graph_.LoadGraphFromFile("/Users/glenpoin/W/Projects/Algorithms/SimpleNavigator/materials/examples/graph_1.txt");
  adjacency_matrix_ = graph_.GetGraph();
  if (adjacency_matrix_.GetRows()) {
    qDebug() << adjacency_matrix_.GetRows();
  }
}

void GraphVisualizer::DrawGraph() {
  int rows = adjacency_matrix_.GetRows();
  int cols = adjacency_matrix_.GetCols();


  for (int row = 0; row < rows; ++row) {
    QGraphicsEllipseItem* vertex = addEllipse(0, 0, 30, 30);
    vertex->setPos(qrand() % 300, qrand() % 300);
    QGraphicsTextItem* textItem = new QGraphicsTextItem(QString::number(row), vertex);
    textItem->setPos(8, 8);

    vertices_.append(vertex);
  }
}
