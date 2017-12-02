#include "luna.h"

#include <algorithm>

#include <QtQuick>
#include <QPluginLoader>
#include <QDir>
#include <QDebug>

#include "lunaplugin.h"

namespace luna {
    Luna::Luna(QObject * parent) :
        QObject(parent),
        mEngine(new QQmlApplicationEngine(this)),
        mActiveTab(-1)
    {
    }

    void Luna::setup() {
        loadStaticPlugins();
        loadDynamicPlugins();
        for (auto & plugin : mPlugins) {
            plugin->initialize(this);
        }

        auto rootContext = mEngine->rootContext();
        rootContext->setContextProperty("TabNames", mTabNames);

        mEngine->load(QUrl("qrc:/main.qml"));

        instantiateTabs();

        setSelectedIndex(0);
    }

    Manager & Luna::manager() {
        return mManager;
    }

    void Luna::loadDynamicPlugins() {
        QDir pluginsDir(qApp->applicationDirPath());
        pluginsDir.cd("plugins");

        qDebug() << "Loading plugins from " << pluginsDir.absolutePath();

        for (auto fileName : pluginsDir.entryList(QDir::Files)) {
            if (!QLibrary::isLibrary(fileName)) {
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
    }

    void Luna::loadStaticPlugins() {

    }

    void Luna::instantiateTabs() {
        std::sort(mTabs.begin(), mTabs.end(),
            [](const auto & a, const auto & b) -> bool {
                return a->displayOrder() < b->displayOrder();
            }
        );

        auto rootContext = mEngine->rootContext();
        auto root = mEngine->rootObjects().first();
        auto swipeView = root->findChild<QQuickItem *>("swipeView");

        for (auto & tab : mTabs) {
            qInfo() << "Loading " << tab->displayName() << ", url: " << tab->itemUrl();
            QQmlComponent component(mEngine, tab->itemUrl());
            if (!component.isReady()) {
                qWarning() << "Error. Failed to load tab";
                continue;
            }

            auto context = new QQmlContext(rootContext, mEngine);
            auto object = component.create(context);

            if (nullptr == object) {
                qWarning() << "Failed to create tab.";
                delete object;
                continue;
            }

            auto quickItem = qobject_cast<QQuickItem *>(object);
            if (nullptr == quickItem) {
                qWarning() << "Created tab is not a QItem.";
                delete quickItem;
            }

            context->setContextProperty(tab->displayName(), tab->model());
            quickItem->setParent(mEngine);
            quickItem->setParentItem(swipeView);
            mTabNames.append(tab->displayName());
        }

        QObject::connect(swipeView, SIGNAL(indexChanged(int)),
            this, SLOT(setSelectedIndex(int)));

        rootContext->setContextProperty("TabNames", mTabNames);
    }

    void Luna::setSelectedIndex(int index) {
        if (mActiveTab >= 0) {
            mTabs[mActiveTab]->enabled(false);
        }
        mActiveTab = index;
        mTabs[mActiveTab]->enabled(true);
    }
}
