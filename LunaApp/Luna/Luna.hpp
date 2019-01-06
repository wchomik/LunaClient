#pragma once

#include <vector>
#include <memory>

#include <QObject>
#include <QtQuick>
#include <QQmlContext>
#include <QQmlApplicationEngine>

#include <lunacore/manager.h>

#include "luna/interface/LunaPlugin.hpp"
#include "luna/interface/Effectplugin.hpp"
#include "luna/interface/Connectorplugin.hpp"

class Luna : public QObject
{
    Q_OBJECT
public:
    explicit Luna();
    ~Luna();

    void setup();
    void addEffect(std::unique_ptr<EffectPlugin> && effect);
    void addConnector(std::unique_ptr<ConnectorPlugin> && connector);
private:
    using PluginPtr = std::unique_ptr<lunacore::LunaPlugin>;
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
    lunacore::Manager mManager;
    PluginVector mPlugins;

    EffectVector mEffects;
    class TabsModel * mEffectsModel;

    ConnectorVector mConnectors;
    class TabsModel * mConnectorsModel;
private slots:
    void setSelectedIndex(int index);
};
