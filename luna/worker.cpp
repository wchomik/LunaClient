#include "worker.h"

#include <QTimer>

#include "manager.h"

namespace luna {
    Worker::Worker(QObject * parent) :
        QThread(parent),
        mLunaManager(nullptr),
        mSettings("Luna", "Luna")
    {
        mLunaManager = new Manager();
        mLunaManager->moveToThread(this);

        mRedBalance = mSettings.value("redBalance", 1.0).toReal();
        mGreenBalance = mSettings.value("greenBalance", 1.0).toReal();
        mBlueBalance = mSettings.value("blueBalance", 1.0).toReal();
        updateWhiteBalance();
    }

    Worker::~Worker()
    {
        quit();
        wait();
        mSettings.setValue("redBalance", mRedBalance);
        mSettings.setValue("blueBalance", mBlueBalance);
        mSettings.setValue("greenBalance", mGreenBalance);
        mSettings.sync();
    }

    void Worker::setRedBalance(qreal value)
    {
        if(mRedBalance != value){
            mRedBalance = value;
            updateWhiteBalance();
            redBalanceChanged();
        }
    }

    void Worker::setGreenBalance(qreal value)
    {
        if(mGreenBalance != value){
            mGreenBalance = value;
            updateWhiteBalance();
            greenBalanceChanged();
        }
    }

    void Worker::setBlueBalance(qreal value)
    {
        if(mBlueBalance != value){
            mBlueBalance = value;
            updateWhiteBalance();
            blueBalanceChanged();
        }
    }

    void Worker::run(){
        QThread::exec();
        delete mLunaManager;
        mLunaManager = nullptr;
    }

    void Worker::updateWhiteBalance()
    {
        mLunaManager->setWhiteBalance(Color(mRedBalance, mGreenBalance, mBlueBalance, 1));
        QTimer::singleShot(0, mLunaManager, &Manager::updateColorMode);
    }
}
