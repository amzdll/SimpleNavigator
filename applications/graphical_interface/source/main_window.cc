#include "main_window.h"

#include <QLabel>
#include "QDir"
#include "../ui/ui_main_window.h"


GraphicalInterface::GraphicalInterface(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::GraphicalInterface) {

  QPixmap pixmap(
      "../../../applications/graphical_interface/static/img/stripped_background.png");
  QLabel* label = new QLabel(this);

  label->setPixmap(pixmap);
  label->setAlignment(Qt::AlignCenter);
  setCentralWidget(label);

  graph_visualizer_ = new GraphVisualizer(this);
  interaction_panel_ = new InteractionPanel(graph_visualizer_, this);
  ui->setupUi(this);
  ui->interaction_panel->addWidget(interaction_panel_);
  ui->graph_visualizer->addWidget(graph_visualizer_);
}

GraphicalInterface::~GraphicalInterface() {
  delete interaction_panel_;
  delete graph_visualizer_;
  delete ui;
}
