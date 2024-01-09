#include <QApplication>
#include <QFontDatabase>

#include "QMessageBox"
#include "include/main_window.h"

int main(int argc, char *argv[]) {
  QApplication application(argc, argv);
  QApplication::setWindowIcon(QIcon(":/resource/img/logo.jpeg"));
//  QFontDatabase::addApplicationFont(
//      ":/fonts/font/LiberationMono-Regular.ttf");
  int id =  QFontDatabase::addApplicationFont(":/resource/font/JetBrainsMono.ttf");
  QStringList fontFamilies = QFontDatabase::applicationFontFamilies(id);
  QString fontNames;
  for (const QString &fontFamily : fontFamilies) {
    fontNames += fontFamily + "\n";
  }
  QMessageBox::information(nullptr, "Message","Added Font Families:\n" + fontNames);

  QFile style_file(":/resource/style.qss");
  style_file.open(QFile::ReadOnly);
  qApp->setStyleSheet(QLatin1String(style_file.readAll()));
  GraphicalInterface w;
  w.show();
  return application.exec();
}
