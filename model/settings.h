#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>
#include <QColor>

#include "../luna/manager.h"
#include "../luna/provider.h"

#include "lightprovidersettings.h"

namespace model {
    class Settings : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(qreal redBalance READ redBalance WRITE setRedBalance NOTIFY redBalanceChanged)
        Q_PROPERTY(qreal greenBalance READ greenBalance WRITE setGreenBalance NOTIFY greenBalanceChanged)
        Q_PROPERTY(qreal blueBalance READ blueBalance WRITE setBlueBalance NOTIFY blueBalanceChanged)
        Q_PROPERTY(QString provider WRITE setProvider)
        Q_PROPERTY(LightProviderSettings * light READ light)
    public:
        explicit Settings(QObject *parent = 0);
        ~Settings();
        void setLunaManager(luna::Manager * manager);

        void setProvider(const QString & name);

        qreal redBalance() const { return mRedBalance; }
        void setRedBalance(qreal value);
        qreal greenBalance() const { return mGreenBalance; }
        void setGreenBalance(qreal value);
        qreal blueBalance() const { return mBlueBalance; }
        void setBlueBalance(qreal value);

        LightProviderSettings * light(){ return &mLightSettings; }
    signals:
        void redBalanceChanged();
        void greenBalanceChanged();
        void blueBalanceChanged();
        void lightColorChanged();
    private:
        void updateWhiteBalance();

        luna::Manager * mManager;
        QSettings mSettings;
        LightProviderSettings mLightSettings;

        qreal mRedBalance;
        qreal mGreenBalance;
        qreal mBlueBalance;
        QColor mLightColor;
    };
}

#endif // SETTINGS_H
