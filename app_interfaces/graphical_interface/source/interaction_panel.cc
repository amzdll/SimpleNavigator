#include "interaction_panel.h"

#include "../ui/ui_interaction_panel.h"

InteractionPanel::InteractionPanel(GraphVisualizer *graph_visualizer, QWidget *parent)
    : QWidget(parent), ui(new Ui::InteractionPanel), graph_visualizer_(graph_visualizer) {
  ui->setupUi(this);

  QDoubleValidator *double_validator = new QDoubleValidator();
  ui->DFS_Input->setValidator(double_validator);
  ui->BFS_Input->setValidator(double_validator);

  connect(ui->OpenGraph, &QPushButton::clicked, graph_visualizer_, &GraphVisualizer::OpenGraph);
  connect(ui->DFS, &QPushButton::clicked, this, [this]() {
    graph_visualizer_->DFS(ui->DFS_Input->text().toFloat());
  });
  connect(ui->BFS, &QPushButton::clicked, this, [this]() {
    graph_visualizer_->BFS(ui->BFS_Input->text().toFloat());
  });
  connect(ui->Redraw,  &QPushButton::clicked, graph_visualizer_,
          &GraphVisualizer::Redraw);

}

InteractionPanel::~InteractionPanel() { delete ui; }
