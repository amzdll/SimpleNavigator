#ifndef INTERACTION_PANEL_H
#define INTERACTION_PANEL_H

#include <QDoubleValidator>
#include <QWidget>

#include "graph_visualizer.h"

namespace Ui {
class InteractionPanel;

}
class GraphVisualizer;
class InteractionPanel : public QWidget {
  Q_OBJECT

 public:
  explicit InteractionPanel(GraphVisualizer *graph_visualizer,
                            QWidget *parent = nullptr);
  ~InteractionPanel();

 private:
  s21::Graph graph_;
  GraphVisualizer *graph_visualizer_;
  Ui::InteractionPanel *ui;

  void ConnectSignals();
// private slots:
  void FillTable();
  void GetShortestPathBetweenVertices();
  void GetShortestPathBetweenAllVertices();
  void OpenGraph();
};

#endif  // INTERACTION_PANEL_H
