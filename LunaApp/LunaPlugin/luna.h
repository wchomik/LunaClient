#ifndef LUNA_H
#define LUNA_H

#include <vector>
#include <memory>

#include <QObject>
#include <QtQuick>
#include <QQmlContext>
#include <QQmlApplicationEngine>

#include <manager.h>

#include "lunaplugin_global.h"
#include "lunaplugin.h"
#include "effectplugin.h"
#include "connectorplugin.h"

namespace luna {
    class LUNAPLUGINSHARED_EXPORT Luna : public QObject
    {
        Q_OBJECT
    public:
        explicit Luna(QObject *parent = nullptr);
        ~Luna();

        void setup();
        void addEffect(std::unique_ptr<EffectPlugin> && effect);
        void addConnector(std::unique_ptr<ConnectorPlugin> && connector);
        Manager & manager();
    private:
        using PluginPtr = std::unique_ptr<luna::LunaPlugin>;
        using PluginVector = std::vector<PluginPtr>;

        using EffectPtr = std::unique_ptr<EffectPlugin>;
        using EffectVector = std::vector<EffectPtr>;

        using ConnectorPtr = std::unique_ptr<ConnectorPlugin>;
        using ConnectorVector = std::vector<ConnectorPtr>;

        void loadDynamicPlugins();
        void loadStaticPlugins();
        QQuickItem * instantiateTab(ConfigurablePlugin * plugin);
        void instantiateTabs();

        QQmlApplicationEngine * mEngine;
        luna::Manager mManager;
        PluginVector mPlugins;

        EffectVector mEffects;
        class TabsModel * mEffectsModel;

        ConnectorVector mConnectors;
        class TabsModel * mConnectorsModel;
    private slots:
        void setSelectedIndex(int index);
    };
}

#endif // LUNA_H
