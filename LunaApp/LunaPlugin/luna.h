#ifndef LUNA_H
#define LUNA_H

#include <vector>
#include <memory>
#include <manager.h>

#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QtQuick>
#include <QObject>
#include <QList>

#include <lunaplugin.h>

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
        void addTab(std::unique_ptr<Tab> && tab);
        Manager & manager();
    private:
        using PluginPtr = std::unique_ptr<luna::LunaPlugin>;
        using PluginVector = std::vector<PluginPtr>;

        using TabPtr = std::unique_ptr<Tab>;
        using TabVector = std::vector<TabPtr>;


        void loadDynamicPlugins();
        void loadStaticPlugins();
        void instantiateTabs();


        QQmlApplicationEngine * mEngine;
        luna::Manager mManager;
        PluginVector mPlugins;

        TabVector mTabs;
        class TabsModel * mModesModel;
        class TabsModel * mConnectorsModel;
        int mActiveTab;
    private slots:
        void setSelectedIndex(int index);
    };
}

#endif // LUNA_H
