#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <manager.h>
#include "model/settings.h"

#include <lunaplugin.h>

#include <vector>
#include <memory>
#include <QDir>
#include <QPluginLoader>
#include <QDebug>
#include "luna/illuminationprovider.h"


using PluginPtr = std::unique_ptr<luna::LunaPlugin>;
using PluginVector = std::vector<PluginPtr>;

PluginVector loadPlugins() {
    QDir pluginsDir(qApp->applicationDirPath());
    #if defined(Q_OS_WIN)
    if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release") {
        pluginsDir.cdUp();
        pluginsDir.cdUp();
    }
    #endif
    pluginsDir.cd("plugins");

    qDebug() << "Loading plugins from " << pluginsDir.absolutePath();

    PluginVector plugins;
    for (auto fileName : pluginsDir.entryList(QDir::Files)) {
        qDebug() << "Plugin: " << fileName;
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject * plugin = pluginLoader.instance();
        if (plugin) {
            qDebug() << "Maybe";
            auto lunaPlugin = qobject_cast<luna::LunaPlugin *>(plugin);
            if (nullptr != lunaPlugin) {
                qDebug() << "Compatible";
                plugins.emplace_back(lunaPlugin);
            }
        }
    }
    return plugins;
}


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    qputenv("QT_QUICK_CONTROLS_1_STYLE", "Flat");
    QGuiApplication app(argc, argv);

    auto plugins = loadPlugins();
    qDebug() << "Found " << plugins.size() << " plugins";


    luna::Manager manager;
    manager.setProvider(std::make_unique<luna::IlluminationProvider>());
    model::Settings settings;
    settings.setLunaManager(&manager);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("Luna", &settings);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    int ret = app.exec();

    return ret;
}
