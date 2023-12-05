#include "../include/graph_visualizer.h"

#include "../ui/ui_graph_visualizer.h"

GraphVisualizer::GraphVisualizer(QWidget *parent)
    : QWidget(parent), ui(new Ui::GraphVisualizer) {
  ui->setupUi(this);
}

GraphVisualizer::~GraphVisualizer() { delete ui; }
