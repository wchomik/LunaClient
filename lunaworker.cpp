#include "lunaworker.h"

#include <QTimer>

#include "lunamanager.h"

namespace luna {
    LunaWorker::LunaWorker(QObject * parent) :
        QThread(parent),
        mLunaManager(nullptr),
        mSettings("Luna", "Luna")
    {
        mLunaManager = new LunaManager();
        mLunaManager->moveToThread(this);

        mRedBalance = mSettings.value("redBalance", 1.0).toReal();
        mGreenBalance = mSettings.value("greenBalance", 1.0).toReal();
        mBlueBalance = mSettings.value("blueBalance", 1.0).toReal();
        updateWhiteBalance();
    }

    LunaWorker::~LunaWorker()
    {
        quit();
        wait();
        mSettings.setValue("redBalance", mRedBalance);
        mSettings.setValue("blueBalance", mBlueBalance);
        mSettings.setValue("greenBalance", mGreenBalance);
        mSettings.sync();
    }

    void LunaWorker::setRedBalance(qreal value)
    {
        if(mRedBalance != value){
            mRedBalance = value;
            updateWhiteBalance();
            redBalanceChanged();
        }
    }

    void LunaWorker::setGreenBalance(qreal value)
    {
        if(mGreenBalance != value){
            mGreenBalance = value;
            updateWhiteBalance();
            greenBalanceChanged();
        }
    }

    void LunaWorker::setBlueBalance(qreal value)
    {
        if(mBlueBalance != value){
            mBlueBalance = value;
            updateWhiteBalance();
            blueBalanceChanged();
        }
    }

    void LunaWorker::run(){
        QThread::exec();
        delete mLunaManager;
        mLunaManager = nullptr;
    }

    void LunaWorker::updateWhiteBalance()
    {
        mLunaManager->setWhiteBalance(Color(mRedBalance, mGreenBalance, mBlueBalance, 1));
        QTimer::singleShot(0, mLunaManager, &LunaManager::updateColorMode);
    }
}
