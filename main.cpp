#include <QApplication>
#include <QQmlApplicationEngine>
#include "core.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Core core;
    return app.exec();
    //D:
}

