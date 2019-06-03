#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    /*w.setMaximumSize(615,580);
    w.setMinimumSize(615,580);*/
    w.show();
    return a.exec();
}
