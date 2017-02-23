#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "luna/worker.h"
#include "model/settings.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    qputenv("QT_QUICK_CONTROLS_1_STYLE", "Flat");
    QGuiApplication app(argc, argv);

    luna::Worker worker;
    model::Settings settings;
    settings.setLunaManager(worker.lunaManager());
    worker.start();

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("Luna", &settings);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    int ret = app.exec();

    worker.quit();
    worker.wait();
    return ret;
}
