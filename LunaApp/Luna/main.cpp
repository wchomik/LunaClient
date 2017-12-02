#include <QGuiApplication>

#include <QDebug>

#include <luna.h>

using namespace luna;

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
