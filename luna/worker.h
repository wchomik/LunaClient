#ifndef LUNAWORKER_H
#define LUNAWORKER_H

#include <QThread>
#include <QColor>
#include <QSettings>

#include "manager.h"

namespace luna {
    class Worker : public QThread
    {
    public:
        explicit Worker(QObject * parent = nullptr);
        class Manager * lunaManager(){ return mLunaManager; }
    protected:
        void run() override;
    private:
        class Manager * mLunaManager;
    };
}

#endif // LUNAWORKER_H
