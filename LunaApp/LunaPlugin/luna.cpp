#include "luna.h"

#include <algorithm>

#include <QtQuick>
#include <QPluginLoader>
#include <QDir>
#include <QDebug>

#include "lunaplugin.h"
#include "tabsmodel.h"

namespace luna {
    Luna::Luna(QObject * parent) :
        QObject(parent),
        mEngine(new QQmlApplicationEngine(this)),
        mEffectsModel(new TabsModel(this)),
        mConnectorsModel(new TabsModel(this))
    {
        QObject::connect(mEffectsModel, &TabsModel::tabSelected,
            this, &Luna::setSelectedIndex);
    }

    Luna::~Luna() {}

    void Luna::setup() {
        loadStaticPlugins();
        loadDynamicPlugins();
        for (auto & plugin : mPlugins) {
            plugin->initialize(this);
        }

        instantiateTabs();

        auto rootContext = mEngine->rootContext();
        rootContext->setContextProperty("EffectsModel", mEffectsModel);
        rootContext->setContextProperty("ConnectorsModel", mConnectorsModel);

        mEngine->load(QUrl("qrc:/main.qml"));

        setSelectedIndex(0);
    }

    void Luna::addEffect(std::unique_ptr<EffectPlugin> && tab) {
        mEffects.emplace_back(std::move(tab));
    }

    Manager & Luna::manager() {
        return mManager;
    }

    void Luna::loadDynamicPlugins() {
        QDir pluginsDir(qApp->applicationDirPath());
        pluginsDir.cd("plugins");

        qDebug() << "Loading plugins from" << pluginsDir.absolutePath();

        for (auto fileName : pluginsDir.entryList(QDir::Files)) {
            if (!QLibrary::isLibrary(fileName)) {
                continue;
            }

            QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
            if (!pluginLoader.load()) {
                qDebug() << "Failed to load" << fileName;
                qDebug() <<  pluginLoader.errorString();
                continue;
            }
            QObject * plugin = pluginLoader.instance();
            if (plugin) {
                auto lunaPlugin = qobject_cast<luna::LunaPlugin *>(plugin);
                if (nullptr != lunaPlugin) {
                    qDebug() << fileName << "loaded";
                    mPlugins.emplace_back(lunaPlugin);
                }
            }
        }
    }

    void Luna::loadStaticPlugins() {

    }

    void Luna::instantiateTabs() {
        std::sort(mEffects.begin(), mEffects.end(),
            [](const auto & a, const auto & b) -> bool {
                return a->displayOrder() < b->displayOrder();
            }
        );

        auto rootContext = mEngine->rootContext();

        for (auto & tab : mEffects) {
            qInfo() << "Loading" << tab->displayName() << tab->itemUrl();
            QQmlComponent component(mEngine, tab->itemUrl());
            if (!component.isReady()) {
                qWarning() << "Error. Failed to load tab";
                continue;
            }

            auto context = new QQmlContext(rootContext, mEngine);
            context->setContextProperty(tab->displayName(), tab->model());

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

            quickItem->setParent(mEngine);
            QString name = tab->displayName();
            mEffectsModel->addTab(quickItem, name);
        }
    }

    void Luna::setSelectedIndex(int index) {
        mManager.setProvider(mEffects[index]->createProvider());
    }
}
