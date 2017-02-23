#include "worker.h"

#include <QTimer>

#include "manager.h"

namespace luna {
    Worker::Worker(QObject * parent) :
        QThread(parent),
        mLunaManager(nullptr)
    {
        mLunaManager = new Manager();
        mLunaManager->moveToThread(this);
    }

    void Worker::run(){
        QThread::exec();
        delete mLunaManager;
        mLunaManager = nullptr;
    }
}
