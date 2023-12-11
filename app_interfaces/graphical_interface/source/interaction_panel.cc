#include "interaction_panel.h"

#include "../ui/ui_interaction_panel.h"

InteractionPanel::InteractionPanel(GraphVisualizer *graph_visualizer, QWidget *parent)
    : QWidget(parent), ui(new Ui::InteractionPanel), graph_visualizer_(graph_visualizer) {
  ui->setupUi(this);


  connect(ui->OpenGraph, &QPushButton::clicked, graph_visualizer_, &GraphVisualizer::OpenGraph);
  connect(ui->DFS,  &QPushButton::clicked, graph_visualizer_, &GraphVisualizer::DFC);
}

InteractionPanel::~InteractionPanel() { delete ui; }
