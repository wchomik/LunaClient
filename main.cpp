#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "lunaworker.h"



static QObject *lunaWorkerProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    luna::LunaWorker *example = new luna::LunaWorker();
    return example;
}

int main(int argc, char *argv[])
{

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    qputenv("QT_QUICK_CONTROLS_1_STYLE", "Flat");
    QGuiApplication app(argc, argv);

    qmlRegisterSingletonType<luna::LunaWorker>("luna.LunaWorker", 1, 0, "LunaWorker", lunaWorkerProvider);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
