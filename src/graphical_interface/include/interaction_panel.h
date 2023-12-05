#ifndef INTERACTION_PANEL_H
#define INTERACTION_PANEL_H

#include <QWidget>

namespace Ui {
class InteractionPanel;
}

class InteractionPanel : public QWidget {
  Q_OBJECT

 public:
  explicit InteractionPanel(QWidget *parent = nullptr);
  ~InteractionPanel();

 private:
  Ui::InteractionPanel *ui;
};

#endif  // INTERACTION_PANEL_H
