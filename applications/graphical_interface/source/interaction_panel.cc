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
  ui->path_table->setColumnWidth(0, 150);
  ui->path_table->setColumnWidth(1, 150);
  ui->path_table->setColumnWidth(2, 150);

  // temp
  ui->path_table->insertRow(3);
}

InteractionPanel::~InteractionPanel() { delete ui; }

void InteractionPanel::ConnectSignals() {
  // Open
  connect(ui->open_graph_btn, &QPushButton::clicked, this,
          &InteractionPanel::OpenGraph);
  // DFS & BFS
  connect(ui->dfs_btn, &QPushButton::clicked, this, [this]() {
    graph_visualizer_->DrawPath(s21::GraphAlgorithms::DepthFirstSearch(
        graph_, ui->dfs_input->text().toFloat()));
  });
  connect(ui->bfs_btn, &QPushButton::clicked, this, [this]() {
    graph_visualizer_->DrawPath(s21::GraphAlgorithms::BreadthFirstSearch(
        graph_, ui->dfs_input->text().toFloat()));
  });
  // Shortest path
  connect(ui->get_shortest_path_between_vertices_btn, &QPushButton::clicked,
          this, &InteractionPanel::GetShortestPath);
  connect(ui->path_table, &QTableWidget::itemClicked, this,
          &InteractionPanel::GetShortestPathItemTable);
  connect(ui->get_shortest_paths_between_all_vertices_btn,
          &QPushButton::clicked, this, &InteractionPanel::FillPathsTable);
  // TSM
  connect(ui->tsm_btn, &QPushButton::clicked, this, &InteractionPanel::TSM);
  // Other
  connect(ui->redraw_btn, &QPushButton::clicked, this,
          [this]() { graph_visualizer_->Redraw(graph_); });
}

void InteractionPanel::OpenGraph() {
  QString file_name = QFileDialog::getOpenFileName(
      nullptr, "Выберите файл", "../../../materials/examples", "*.txt");
  if (!file_name.isEmpty()) {
    if (graph_.LoadGraphFromFile(file_name.toStdString())) {
      graph_visualizer_->OpenGraph(graph_);
    }
  }
}

void InteractionPanel::GetLeastSpanningTree() {}

void InteractionPanel::GetShortestPath() {
  auto path = s21::GraphAlgorithms::GetShortestPathBetweenVertices(
      graph_, ui->first_vertex_shortest_path_input->text().toFloat(),
      ui->end_vertex_shortest_path_input->text().toFloat());
  ui->shortest_path_result->setText(QString::number(path.first));
  graph_visualizer_->DrawPath(path.second);
}

void InteractionPanel::GetShortestPathItemTable() {
  auto path = s21::GraphAlgorithms::GetShortestPathBetweenVertices(
      graph_,
      ui->path_table->item(ui->path_table->currentRow(), 0)->text().toFloat(),
      ui->path_table->item(ui->path_table->currentRow(), 1)->text().toFloat());
  graph_visualizer_->DrawPath(path.second);
}

void InteractionPanel::FillPathsTable() {
  auto shortest_paths =
      s21::GraphAlgorithms::GetShortestPathsBetweenAllVertices(graph_);

  ui->path_table->clearContents();
  ui->path_table->setRowCount(0);

  for (int row = 1; row < shortest_paths.GetRows(); ++row) {
    for (int col = 1; col < shortest_paths.GetCols(); ++col) {
      ui->path_table->insertRow(ui->path_table->rowCount());
      ui->path_table->setItem(
          ui->path_table->rowCount() - 1, 0,
          new QTableWidgetItem(QString::number(graph_.GetGraph()[row][0])));
      ui->path_table->setItem(
          ui->path_table->rowCount() - 1, 1,
          new QTableWidgetItem(QString::number(graph_.GetGraph()[0][col])));
      ui->path_table->setItem(
          ui->path_table->rowCount() - 1, 2,
          new QTableWidgetItem(
              graph_.GetGraph()[row][col] == 0
                  ? "-"
                  : QString::number(graph_.GetGraph()[row][col])));
    }
  }
}

void InteractionPanel::TSM() {
  s21::GraphAlgorithms::TsmResult tsm_result =
      s21::GraphAlgorithms::SolveTravelingSalesmanProblem(graph_);
  graph_visualizer_->TSM(tsm_result);
}
