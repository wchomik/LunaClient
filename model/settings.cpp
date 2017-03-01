#include "settings.h"

#include "luna/colorutils.h"

namespace model {
    Settings::Settings(QObject *parent) :
        QObject(parent),
        mSettings(QSettings::IniFormat, QSettings::UserScope, "Luna", "Luna", this),
        mLightSettings(this)
    {
        qRegisterMetaType<luna::ProviderType>("luna::ProviderType");
    }

    Settings::~Settings()
    {
        mSettings.setValue("redBalance", mRedBalance);
        mSettings.setValue("blueBalance", mBlueBalance);
        mSettings.setValue("greenBalance", mGreenBalance);
        mSettings.sync();
    }

    void Settings::setLunaManager(luna::Manager *manager)
    {
        mManager = manager;
        mRedBalance = mSettings.value("redBalance", 1.0).toReal();
        mGreenBalance = mSettings.value("greenBalance", 1.0).toReal();
        mBlueBalance = mSettings.value("blueBalance", 1.0).toReal();
        updateWhiteBalance();
        mLightSettings.setSettings(&mSettings);
    }

    void Settings::setRedBalance(qreal value)
    {
        if(mRedBalance != value){
            mRedBalance = value;
            updateWhiteBalance();
            redBalanceChanged();
        }
    }

    void Settings::setGreenBalance(qreal value)
    {
        if(mGreenBalance != value){
            mGreenBalance = value;
            updateWhiteBalance();
            greenBalanceChanged();
        }
    }

    void Settings::setBlueBalance(qreal value)
    {
        if(mBlueBalance != value){
            mBlueBalance = value;
            updateWhiteBalance();
            blueBalanceChanged();
        }
    }

    void Settings::setProvider(const QString &name)
    {
        luna::ProviderType type = luna::ProviderType::none;
        if(name == "Light"){
            type = luna::ProviderType::illumination;
        }else if(name == "Display"){
            type = luna::ProviderType::screen;
        }else if(name == "Audio"){
            type = luna::ProviderType::audio;
        }
        mManager->setMode(type);

        luna::Provider * provider = mManager->currentProvider();

        mLightSettings.setProvider(provider);
    }

    void Settings::updateWhiteBalance()
    {
        mManager->setWhiteBalance(luna::Color(mRedBalance, mGreenBalance, mBlueBalance, 1));
    }
}
