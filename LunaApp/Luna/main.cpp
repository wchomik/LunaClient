#include <QGuiApplication>

#include <QDebug>

#include "luna.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    Luna luna;
    luna.setup();

    return app.exec();
}
