#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("五子棋");
    w.show();
    w.newgame->exec();
    return a.exec();
}
