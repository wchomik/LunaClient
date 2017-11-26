#ifndef LUNA_H
#define LUNA_H

#include <vector>
#include <memory>
#include <manager.h>

#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QObject>

#include <lunaplugin.h>

class Luna : public QObject
{
    Q_OBJECT
public:
    explicit Luna(QObject *parent = nullptr);

    void setup();
private:

    using PluginPtr = std::unique_ptr<luna::LunaPlugin>;
    using PluginVector = std::vector<PluginPtr>;

    void loadDynamicPlugins();

    QQmlApplicationEngine * mEngine;
    luna::Manager mManager;
    PluginVector mPlugins;
public slots:
    void setSelectedIndex(int index);
};

#endif // LUNA_H
