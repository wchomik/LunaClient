#ifndef LUNAWORKER_H
#define LUNAWORKER_H

#include <QThread>
#include <QColor>
#include <QSettings>

#include "lunamanager.h"

namespace luna {
    class LunaWorker : public QThread
    {
        Q_OBJECT
        Q_PROPERTY(qreal redBalance READ redBalance WRITE setRedBalance NOTIFY redBalanceChanged)
        Q_PROPERTY(qreal greenBalance READ greenBalance WRITE setGreenBalance NOTIFY greenBalanceChanged)
        Q_PROPERTY(qreal blueBalance READ blueBalance WRITE setBlueBalance NOTIFY blueBalanceChanged)

    public:
        explicit LunaWorker(QObject * parent = nullptr);
        ~LunaWorker();

        qreal redBalance(){ return mRedBalance; }
        void setRedBalance(qreal value);
        qreal greenBalance(){ return mGreenBalance; }
        void setGreenBalance(qreal value);
        qreal blueBalance(){ return mBlueBalance; }
        void setBlueBalance(qreal value);

    signals:
        void redBalanceChanged();
        void greenBalanceChanged();
        void blueBalanceChanged();

    protected:
        void run() override;
    private:
        void updateWhiteBalance();

        class LunaManager * mLunaManager;

        QSettings mSettings;

        qreal mRedBalance;
        qreal mGreenBalance;
        qreal mBlueBalance;
    };
}

#endif // LUNAWORKER_H
