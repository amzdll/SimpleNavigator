#ifndef INTERACTION_PANEL_H
#define INTERACTION_PANEL_H

#include <QDoubleValidator>
#include <QWidget>

#include "graph_visualizer.h"

namespace Ui {
class InteractionPanel;
}

class InteractionPanel : public QWidget {
  Q_OBJECT

 public:
  explicit InteractionPanel(GraphVisualizer *graph_visualizer,
                            QWidget *parent = nullptr);
  ~InteractionPanel();

 private:
  GraphVisualizer *graph_visualizer_;
  Ui::InteractionPanel *ui;
};

#endif  // INTERACTION_PANEL_H
