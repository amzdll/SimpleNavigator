#include "interaction_panel.h"

#include "../ui/ui_interaction_panel.h"

InteractionPanel::InteractionPanel(GraphVisualizer *graph_visualizer,
                                   QWidget *parent)
    : QWidget(parent),
      ui(new Ui::InteractionPanel),
      graph_visualizer_(graph_visualizer) {
  ui->setupUi(this);
  ConnectSignals();

  // refactor
  auto *double_validator = new QDoubleValidator();
  ui->dfs_input->setValidator(double_validator);
  ui->bfs_input->setValidator(double_validator);
  ui->path_table->setColumnWidth(0, 151);
  ui->path_table->setColumnWidth(1, 150);
  ui->path_table->setColumnWidth(2, 151);

  // temp
  ui->path_table->insertRow(3);
}

InteractionPanel::~InteractionPanel() { delete ui; }

void InteractionPanel::ConnectSignals() {
  connect(ui->open_graph_btn, &QPushButton::clicked, graph_visualizer_,
          &GraphVisualizer::OpenGraph);
  connect(ui->dfs_btn, &QPushButton::clicked, this, [this]() {
    graph_visualizer_->DFS(ui->dfs_input->text().toFloat());
  });
  connect(ui->bfs_btn, &QPushButton::clicked, this, [this]() {
    graph_visualizer_->BFS(ui->bfs_input->text().toFloat());
  });
  connect(ui->redraw_btn, &QPushButton::clicked, graph_visualizer_,
          &GraphVisualizer::Redraw);
  connect(ui->tsm_btn, &QPushButton::clicked, graph_visualizer_,
          &GraphVisualizer::TSM);
  connect(ui->path_table, &QTableWidget::itemClicked, this, [this]() {
    graph_visualizer_->GetShortestPathBetweenTwoVertices(
        // refactor:: Need validate
        ui->path_table->item(ui->path_table->currentRow(), 0)->text().toFloat(),
        ui->path_table->item(ui->path_table->currentRow(), 1)
            ->text()
            .toFloat());
  });
  connect(ui->get_shortest_paths_between_all_vertices_btn,
          &QPushButton::clicked, this, &InteractionPanel::FillTable);
}

void InteractionPanel::FillTable() {
  auto *item1 = new QTableWidgetItem("1");
  auto *item2 = new QTableWidgetItem("5");
  auto *item12 = new QTableWidgetItem("3");
  auto *item22 = new QTableWidgetItem("33");
  ui->path_table->insertRow(ui->path_table->rowCount());
  ui->path_table->insertRow(ui->path_table->rowCount());
  ui->path_table->setItem(0, 0, item1);
  ui->path_table->setItem(0, 1, item2);
  ui->path_table->setItem(1, 0, item12);
  ui->path_table->setItem(1, 1, item22);
}
