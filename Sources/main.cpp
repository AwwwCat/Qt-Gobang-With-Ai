#include "../Headers/Gobang.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Gobang w;

    w.move((QApplication::desktop()->width() - 1577) / 2, (QApplication::desktop()->height() - 1277) / 2);
    w.show();
    w.openGame();
    return a.exec();
}
