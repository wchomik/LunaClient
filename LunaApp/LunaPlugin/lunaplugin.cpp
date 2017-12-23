#include "lunaplugin.h"

#include <QDebug>
#include <QQmlEngine>
#include <QQmlContext>
#include <QLocale>
#include <QCoreApplication>

namespace luna {
    LunaPlugin::LunaPlugin(QObject *parent) :
        QObject(parent),
        mTranslator(nullptr)
    {}

    LunaPlugin::~LunaPlugin() {}

    void LunaPlugin::loadTranslation() {
        mTranslator = new QTranslator(this);

        mTranslator->load(QLocale(), "translation", ".", ":/" + name());
        qApp->installTranslator(mTranslator);
    }

    void LunaPlugin::unloadTranslation() {
        qApp->removeTranslator(mTranslator);
        delete mTranslator;
        mTranslator = nullptr;
    }
}

