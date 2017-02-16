#include "lunaworker.h"

#include <QTimer>
#include <iostream>

#include "lunamanager.h"

namespace luna {
    LunaWorker::LunaWorker(QObject * parent) :
        QThread(parent),
        mLunaManager(nullptr)
    {
    }

    void LunaWorker::run(){
        init();
        QThread::exec();
        cleanup();
    }

    void LunaWorker::init(){
        mLunaManager = new LunaManager();
        QObject::connect(this, &LunaWorker::shutdown,
                         mLunaManager, &LunaManager::onShutdown);
    }

    void LunaWorker::cleanup(){
        delete mLunaManager;
    }
}
