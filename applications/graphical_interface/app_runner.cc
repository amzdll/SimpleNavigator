#include <QApplication>
#include <QFontDatabase>

#include "include/main_window.h"


int main(int argc, char *argv[]) {
  QApplication application(argc, argv);

  QFile styleFile(":/styles/style.qss");
  styleFile.open(QFile::ReadOnly);
  QString style = QLatin1String(styleFile.readAll());
  qApp->setStyleSheet(style);
  GraphicalInterface w;
  w.show();
  return application.exec();
}
