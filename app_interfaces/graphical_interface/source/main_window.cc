#include "main_window.h"

#include "../ui/ui_main_window.h"

GraphicalInterface::GraphicalInterface(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::GraphicalInterface) {
  ui->setupUi(this);


  graph_visualizer_ = new GraphVisualizer(this);
  interaction_panel_ = new InteractionPanel(graph_visualizer_ , this);

  ui->interaction_panel->addWidget(interaction_panel_);
  ui->graph_visualizer->addWidget(graph_visualizer_);
}

GraphicalInterface::~GraphicalInterface() {
  delete interaction_panel_;
  delete graph_visualizer_;
  delete ui;
}
