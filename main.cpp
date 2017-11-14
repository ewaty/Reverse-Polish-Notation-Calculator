#include <QApplication>
#include <iostream>
#include <string>
#include <stack>
#include "reversepolish.cpp"
#include "bet.cpp"
#include "qcustomplot.cpp"
#include "mainwindow.h"

using namespace std;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
