#include "bserverwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BserverWindow w;
    w.show();

    return a.exec();
}
