#include "../include/interaction_panel.h"

#include "../ui/ui_interaction_panel.h"

InteractionPanel::InteractionPanel(QWidget *parent)
    : QWidget(parent), ui(new Ui::InteractionPanel) {
  ui->setupUi(this);
}

InteractionPanel::~InteractionPanel() { delete ui; }
