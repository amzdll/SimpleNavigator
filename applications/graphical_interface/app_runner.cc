#include <QApplication>
#include <QFontDatabase>

#include "include/main_window.h"
//font: "/home/freiqq/Other/SimpleNavigator/applications/graphical_interface/static/font/ShareTechMono-Regular.ttf";

int main(int argc, char *argv[]) {
  QApplication application(argc, argv);

  QFontDatabase::addApplicationFont(
      "/home/freiqq/Other/SimpleNavigator/applications/graphical_interface/"
      "static/font/ShareTechMono-Regular.ttf");
  QFile styleFile(
      "/home/freiqq/Other/SimpleNavigator/applications/graphical_interface/"
      "static/style.qss");
  styleFile.open(QFile::ReadOnly);
  QString style = QLatin1String(styleFile.readAll());
  qApp->setStyleSheet(style);
  GraphicalInterface w;
  w.show();
  return application.exec();
}
