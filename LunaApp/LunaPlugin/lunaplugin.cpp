#include "lunaplugin.h"

#include <QDebug>
#include <QQmlEngine>
#include <QQmlContext>

namespace luna {
    LunaPlugin::LunaPlugin(QObject *parent) :
        QObject(parent),
        mTranslator(nullptr)
    {}

    LunaPlugin::~LunaPlugin() {}
}

