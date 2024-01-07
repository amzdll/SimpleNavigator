#include <QApplication>
#include <QFontDatabase>

#include "include/main_window.h"

int main(int argc, char *argv[]) {
  QApplication application(argc, argv);

//  //Font settings
  QFontDatabase::addApplicationFont(":/fonts/font/JetBrainsMono.ttf");
  QFile style_file(":/styles/style.qss");
  style_file.open(QFile::ReadOnly);
  qApp->setStyleSheet(QLatin1String(style_file.readAll()));
  GraphicalInterface w;
  w.show();
  return application.exec();
}
