#ifndef GRAPHICALINTERFACE_H
#define GRAPHICALINTERFACE_H

#include <QMainWindow>

#include "graph_visualizer.h"
#include "interaction_panel.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class GraphicalInterface;
}
QT_END_NAMESPACE

class GraphicalInterface : public QMainWindow {
  Q_OBJECT

 public:
  GraphicalInterface(QWidget *parent = nullptr);
  ~GraphicalInterface();

 private:
  InteractionPanel *interaction_panel_;
  GraphVisualizer *graph_visualizer_;
  Ui::GraphicalInterface *ui;
};
#endif  // GRAPHICALINTERFACE_H
