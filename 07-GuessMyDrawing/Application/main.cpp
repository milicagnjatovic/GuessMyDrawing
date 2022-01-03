#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  MainWindow w("pera");
//  w.attemptConnection(1234);
  w.show();

//  MainWindow w1("mika");
//  w1.attemptConnection(1234);
//  w1.show();

//  MainWindow w2("laza");
//  w2.attemptConnection(1234);
//  w2.show();
  return a.exec();
}

