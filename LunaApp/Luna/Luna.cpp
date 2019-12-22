#include "Luna.hpp"

#include <QtQuick>
#include <QPluginLoader>
#include <QDir>
#include <QDebug>

#include <algorithm>

using namespace luna::interface;

Q_DECLARE_METATYPE(prism::CieXYZ)

QDataStream& operator<<(QDataStream& out, const prism::CieXYZ& v) {
    for (int i = 0; i < 4; ++i) {
        out << v[i];
    }
    return out;
}

QDataStream& operator>>(QDataStream& in, prism::CieXYZ& v) {
    for (int i = 0; i < 4; ++i) {
        in >> v[i];
    }
    return in;
}

Luna::Luna() :
    mEngine(this)
{
    qRegisterMetaTypeStreamOperators<prism::CieXYZ>("CieXYZ");
}

Luna::~Luna() = default;

void Luna::setup() {
    loadDynamicPlugins();
    for (auto & plugin : mPlugins) {
        plugin->initialize(this);
    }

    instantiateTabs();

    mManager.postToThread([this](Manager & manager){
        for (auto & connector : mConnectors) {
            manager.addConnector(connector->createConnector());
        }
    });

    auto rootContext = mEngine.rootContext();
    rootContext->setContextProperty("Luna", this);
    rootContext->setContextProperty("Effects", &mEffectsModel);
    rootContext->setContextProperty("Connectors", &mConnectorsModel);

    mEngine.load(QUrl("qrc:/main.qml"));

    selectEffect(0);
}

void Luna::addEffect(std::unique_ptr<EffectPlugin> && tab) {
    mEffects.emplace_back(std::move(tab));
}

void Luna::addConnector(std::unique_ptr<ConnectorPlugin> && connector) {
    mConnectors.emplace_back(std::move(connector));
}

void Luna::loadDynamicPlugins() {
    QDir pluginsDir(qApp->applicationDirPath());
    pluginsDir.cd("../lib");

    qDebug() << "Loading plugins from" << pluginsDir.absolutePath();

#ifdef WIN32
    auto path = pluginsDir.absolutePath().toStdString();
    SetDllDirectory(path.c_str());
#endif

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
            auto lunaPlugin = qobject_cast<Plugin *>(plugin);
            if (nullptr != lunaPlugin) {
                qDebug() << fileName << "loaded";
                mPlugins.emplace_back(lunaPlugin);
            }
        }
    }
}

std::unique_ptr<QQuickItem> Luna::instantiateTab(Configurable * tab) {
    auto rootContext = mEngine.rootContext();

    QQmlComponent component(&mEngine, tab->itemUrl());
    if (!component.isReady()) {
        qWarning() << "Error. Failed to load tab";
        qWarning() << component.errorString();
        return nullptr;
    }

    auto context = new QQmlContext(rootContext, &mEngine);
    context->setContextProperty("Model", tab->model());

    auto object = component.create(context);

    if (nullptr == object) {
        qWarning() << "Failed to create tab.";
        return nullptr;
    }

    auto quickItem = qobject_cast<QQuickItem *>(object);
    if (nullptr == quickItem) {
        qWarning() << "Created tab is not a QItem.";
        delete object;
        return nullptr;
    }

    return std::unique_ptr<QQuickItem>(quickItem);
}

void Luna::instantiateTabs() {
    std::sort(mEffects.begin(), mEffects.end(),
        [](const auto & a, const auto & b) -> bool {
            return a->displayOrder() < b->displayOrder();
        }
    );

    for (auto & effect : mEffects) {
        if (auto item = instantiateTab(effect.get())) {
            mEffectsModel.add(effect->displayName(), std::move(item));
        }
    }


    std::sort(mConnectors.begin(), mConnectors.end(),
        [](const auto & a, const auto & b) -> bool {
            return a->displayOrder() < b->displayOrder();
        }
    );

    for (auto & connector : mConnectors) {
        if (auto item = instantiateTab(connector.get())) {
            mConnectorsModel.add(connector->displayName(), std::move(item));
        }
    }
}

void Luna::selectEffect(int index) {
    if (index >= 0 && index < mEffects.size()) {
        mManager.postToThread([effect = mEffects[index].get()](Manager & manager){
            manager.setProvider(effect->createProvider());
        });
    }
}
