#include "lunamanager.h"

#include "luna.h"
#include "lunalegacy.h"

#include "lunaprovider.h"
#include "lunailluminationprovider.h"

#include "lunaconfig.h"

namespace luna {
    LunaManager::LunaManager(QObject *parent) :
        QObject(parent),
        mConnectionTimer(this),
        mLuna(nullptr),
        mProvider(nullptr)
    {
        mLuna = new LunaLegacy(this);

        mConnectionTimer.setInterval(100);

        QObject::connect(&mConnectionTimer, &QTimer::timeout, mLuna, &Luna::connect);
        QObject::connect(mLuna, &Luna::connected, this, &LunaManager::onConnected);
        QObject::connect(mLuna, &Luna::disconnected,this, &LunaManager::onDisconnected);

        mConnectionTimer.start();
    }

    void LunaManager::onShutdown()
    {
        QObject::disconnect(mLuna, &Luna::disconnected,this, &LunaManager::onDisconnected);
        mLuna->shutdown();
    }

    void LunaManager::onDataReady()
    {
        mLuna->update(mProvider->pixelStrands(),
                      mProvider->whiteStrands());
    }

    void LunaManager::onConnected(){
        mConnectionTimer.stop();

        LunaIlluminationProvider * illum = new LunaIlluminationProvider(this);

        illum->configure(mLuna->config());
        illum->setUpdateRate(10);
        illum->mColor = Color(1, 0, 1, 0);
        illum->mWhiteness = 0.1f;

        setProvider(illum);
    }

    void LunaManager::onDisconnected(){
        mConnectionTimer.start();
    }

    void LunaManager::setProvider(LunaProvider * provider)
    {
        if(mProvider){
            mProvider->stop();
            QObject::disconnect(mProvider, &LunaProvider::dataReady,
                                this, &LunaManager::onDataReady);
        }
        mProvider = provider;
        if(provider){
            QObject::connect(mProvider, &LunaProvider::dataReady,
                         this, &LunaManager::onDataReady);
            mProvider->start();
        }
    }
}
