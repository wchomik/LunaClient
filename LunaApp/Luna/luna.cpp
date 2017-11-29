#include "luna.h"


#include <QPluginLoader>
#include <QDir>
#include <QDebug>
#include <algorithm>


Luna::Luna(QObject * parent) :
    QObject(parent),
    mEngine(new QQmlApplicationEngine(this))
{
}

void Luna::setup() {
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

void Luna::loadDynamicPlugins() {
    QDir pluginsDir(qApp->applicationDirPath());
    pluginsDir.cd("plugins");

    QCoreApplication::addLibraryPath(pluginsDir.absolutePath());

    qDebug() << "Loading plugins from " << pluginsDir.absolutePath();

    for (auto fileName : pluginsDir.entryList(QDir::Files)) {
        if (!(fileName.endsWith("dll") || fileName.endsWith(".so"))) {
            continue;
        }

        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        if (!pluginLoader.isLoaded()) {
            qDebug() << "Failed to load " << fileName;
            qDebug() <<  pluginLoader.errorString();
        }
        QObject * plugin = pluginLoader.instance();
        if (plugin) {
            auto lunaPlugin = qobject_cast<luna::LunaPlugin *>(plugin);
            if (nullptr != lunaPlugin) {
                qDebug() << fileName << " loaded";
                mPlugins.emplace_back(lunaPlugin);
            }
        }
    }

    std::sort(mPlugins.begin(), mPlugins.end(),
    [](const auto & a, const auto & b) -> bool {
        return a->displayOrder() < b->displayOrder();
    }
             );
}

void Luna::setSelectedIndex(int index) {
    mManager.setProvider(mPlugins[index]->createProvider());
}
