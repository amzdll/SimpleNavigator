#include <QApplication>

#include "include/interface.h"

int main(int argc, char *argv[]) {
  QApplication application(argc, argv);
  GraphicalInterface w;
  w.show();
  return application.exec();
}
