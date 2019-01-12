#include <QGuiApplication>

#include "Luna.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("Luna");
    QCoreApplication::setApplicationName("Luna");
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    Luna luna;
    luna.setup();

    return app.exec();
}
