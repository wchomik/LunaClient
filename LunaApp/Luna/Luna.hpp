#pragma once

#include "Manager.hpp"
#include "TabsModel.hpp"

#include <luna/interface/Plugin.hpp>
#include <luna/interface/Configurable.hpp>
#include <luna/interface/EffectPlugin.hpp>
#include <luna/interface/ConnectorPlugin.hpp>

#include <QObject>
#include <QtQuick>
#include <QQmlContext>
#include <QQmlApplicationEngine>

#include <vector>
#include <memory>

class Luna : public QObject, public luna::interface::Application
{
    Q_OBJECT
public:
    explicit Luna();
    ~Luna() override;

    void setup();
    void addEffect(std::unique_ptr<luna::interface::EffectPlugin> && effect) override;
    void addConnector(std::unique_ptr<luna::interface::ConnectorPlugin> && connector) override;
private:
    using PluginPtr = std::unique_ptr<luna::interface::Plugin>;
    using PluginVector = std::vector<PluginPtr>;

    using EffectPtr = std::unique_ptr<luna::interface::EffectPlugin>;
    using EffectVector = std::vector<EffectPtr>;

    using ConnectorPtr = std::unique_ptr<luna::interface::ConnectorPlugin>;
    using ConnectorVector = std::vector<ConnectorPtr>;

    void loadDynamicPlugins();
    void loadStaticPlugins();
    QQuickItem * instantiateTab(luna::interface::Configurable * plugin);
    void instantiateTabs();

    QQmlApplicationEngine * mEngine;
    Manager mManager;
    PluginVector mPlugins;

    EffectVector mEffects;
    TabsModel * mEffectsModel;

    ConnectorVector mConnectors;
    TabsModel * mConnectorsModel;
private slots:
    void setSelectedIndex(int index);
};
