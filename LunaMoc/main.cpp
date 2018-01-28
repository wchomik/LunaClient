#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QColor>
#include <QQuickView>
#include <QQmlContext>
#include <QVariant>

#include "pixelprovider.h"
#include "udpserver.h"

int main(int argc, char *argv[])
{
    qmlRegisterType<PixelProvider>("MyStuff", 1, 0, "PixelProvider");
    qmlRegisterType<UdpServer>("MyStuff", 1, 0, "UdpServer");

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
