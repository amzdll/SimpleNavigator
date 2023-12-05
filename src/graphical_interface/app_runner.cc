#include <QApplication>

#include "include/graphical_interface.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  GraphicalInterface w;
  w.show();
  return a.exec();
}
