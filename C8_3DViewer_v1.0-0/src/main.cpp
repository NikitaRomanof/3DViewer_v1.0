#include <QApplication>

#include "proto1.h"
#include "widget.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  proto1 w;
  w.show();
  return a.exec();
}
