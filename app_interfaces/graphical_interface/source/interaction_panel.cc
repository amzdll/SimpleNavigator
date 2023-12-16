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

//  connect(ui->GetShortestPathsBetweenAllVertices, &QTableWidgetItem::clicked, this, [this]() {
//    graph_visualizer_->BFS(ui->BFS_Input->text().toFloat());
//  });


  connect(ui->Redraw,  &QPushButton::clicked, graph_visualizer_,
          &GraphVisualizer::Redraw);
  connect(ui->TSM, &QPushButton::clicked, graph_visualizer_, &GraphVisualizer::TSM);


  ui->tableWidget->setColumnWidth(0, 227);
  ui->tableWidget->setColumnWidth(1, 227);

  ui->tableWidget->insertRow(3);

  QTableWidgetItem *item1 = new QTableWidgetItem("1");
  QTableWidgetItem *item2 = new QTableWidgetItem("2 3 4 5 6");
  ui->tableWidget->insertRow(ui->tableWidget->rowCount());
  ui->tableWidget->setItem(0, 0, item1);
  ui->tableWidget->setItem(0, 1, item2);

//  connect(ui->tableWidget, &QTableWidget::itemClicked, this, &MyClassName::onItemClicked);
}

InteractionPanel::~InteractionPanel() { delete ui; }
