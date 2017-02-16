#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "lunaworker.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    qputenv("QT_QUICK_CONTROLS_1_STYLE", "Flat");
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    luna::LunaWorker worker;
    worker.start();
    QObject::connect(&app, &QGuiApplication::aboutToQuit,
                     &worker, &luna::LunaWorker::shutdown);

    int ret = app.exec();

    worker.quit();
    worker.wait();

    return ret;
}
