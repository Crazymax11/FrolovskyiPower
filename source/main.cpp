#include <QApplication>
#include <QQmlApplicationEngine>

#include <app/core.h>
int main(int argc, char *argv[])
{
    Core app(argc, argv);
    return app.exec();
}

