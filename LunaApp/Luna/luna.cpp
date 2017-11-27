#include "luna.h"


#include <QPluginLoader>
#include <QDir>
#include <QDebug>

Luna::Luna(QObject *parent) :
    QObject(parent),
    mEngine(new QQmlApplicationEngine(this))
{
}

void Luna::setup()
{
    loadDynamicPlugins();

    auto rootContext = mEngine->rootContext();
    rootContext->setContextProperty("TabNames", mTabNames);

    mEngine->load(QUrl("qrc:/main.qml"));
    auto root = mEngine->rootObjects().first();
    auto swipeView = root->findChild<QQuickItem *>("swipeView");

    for (auto & plugin : mPlugins) {
        mTabNames.append(plugin->name());

        auto item = plugin->createItem(mEngine);
        item->setParent(mEngine);
        item->setParentItem(swipeView);
    }

    rootContext->setContextProperty("TabNames", mTabNames);

    QObject::connect(swipeView, SIGNAL(indexChanged(int)),
        this, SLOT(setSelectedIndex(int)));

    setSelectedIndex(0);
}

void Luna::loadDynamicPlugins()
{
    QDir pluginsDir(qApp->applicationDirPath());
    #if defined(Q_OS_WIN)
    if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release") {
        pluginsDir.cdUp();
        pluginsDir.cdUp();
    }
    #endif
    pluginsDir.cd("plugins");

    qDebug() << "Loading plugins from " << pluginsDir.absolutePath();

    for (auto fileName : pluginsDir.entryList(QDir::Files)) {
        qDebug() << "Plugin: " << fileName;
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject * plugin = pluginLoader.instance();
        if (plugin) {
            qDebug() << "Maybe";
            auto lunaPlugin = qobject_cast<luna::LunaPlugin *>(plugin);
            if (nullptr != lunaPlugin) {
                qDebug() << "Compatible";
                mPlugins.emplace_back(lunaPlugin);
            }
        }
    }
}

void Luna::setSelectedIndex(int index) {
    mManager.setProvider(mPlugins[index]->createProvider());
}
