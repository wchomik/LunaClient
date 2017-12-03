#ifndef LUNA_H
#define LUNA_H

#include <vector>
#include <memory>

#include <QObject>
#include <QtQuick>
#include <QQmlContext>
#include <QQmlApplicationEngine>

#include <manager.h>

#include "lunaplugin.h"
#include "lunaplugin_global.h"
#include "effectplugin.h"

namespace luna {
    class LUNAPLUGINSHARED_EXPORT Luna : public QObject
    {
        Q_OBJECT
    public:
        explicit Luna(QObject *parent = nullptr);
        ~Luna();

        void setup();
        void addEffect(std::unique_ptr<EffectPlugin> && effect);
        Manager & manager();
    private:
        using PluginPtr = std::unique_ptr<luna::LunaPlugin>;
        using PluginVector = std::vector<PluginPtr>;

        using EffectPtr = std::unique_ptr<EffectPlugin>;
        using EffectVector = std::vector<EffectPtr>;

        void loadDynamicPlugins();
        void loadStaticPlugins();
        void instantiateTabs();

        QQmlApplicationEngine * mEngine;
        luna::Manager mManager;
        PluginVector mPlugins;

        EffectVector mEffects;
        class TabsModel * mEffectsModel;
        class TabsModel * mConnectorsModel;
    private slots:
        void setSelectedIndex(int index);
    };
}

#endif // LUNA_H
