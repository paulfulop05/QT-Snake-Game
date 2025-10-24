#include <QApplication>
#include "mainwindow.h"

int main(int args, char* argv[])
{
    QApplication a {args, argv};

    MainWindow w;
    w.show();

    return a.exec();
}
