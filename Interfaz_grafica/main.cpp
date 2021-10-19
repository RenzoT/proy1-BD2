#include "mainwindow.h"

#include <iostream>
#include <QApplication>

using namespace std;

struct Record{
    string nombre;
    string carrera;
    int ciclo;
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");
    MainWindow w;
    w.show();
    return a.exec();
}
