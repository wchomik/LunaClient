#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>
#include <QColor>

#include "../luna/manager.h"
#include "../luna/provider.h"

namespace model {
    class Settings : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(qreal redBalance READ redBalance WRITE setRedBalance NOTIFY redBalanceChanged)
        Q_PROPERTY(qreal greenBalance READ greenBalance WRITE setGreenBalance NOTIFY greenBalanceChanged)
        Q_PROPERTY(qreal blueBalance READ blueBalance WRITE setBlueBalance NOTIFY blueBalanceChanged)
        Q_PROPERTY(QColor lightColor READ lightColor WRITE setLightColor NOTIFY lightColorChanged)
        Q_PROPERTY(QString provider WRITE setProvider NOTIFY providerChanged)
    public:
        explicit Settings(QObject *parent = 0);
        ~Settings();
        void setLunaManager(luna::Manager * manager);

        qreal redBalance() const { return mRedBalance; }
        void setRedBalance(qreal value);
        qreal greenBalance() const { return mGreenBalance; }
        void setGreenBalance(qreal value);
        qreal blueBalance() const { return mBlueBalance; }
        void setBlueBalance(qreal value);

        QColor lightColor() const { return mLightColor; }
        void setLightColor(const QColor & color);

        QString provider() { return QString(); }
        void setProvider(const QString & name);
    signals:
        void redBalanceChanged();
        void greenBalanceChanged();
        void blueBalanceChanged();
        void lightColorChanged();

    public slots:
        void onProviderChanged();
    private:
        void updateWhiteBalance();

        luna::Manager * mManager;
        QSettings mSettings;

        qreal mRedBalance;
        qreal mGreenBalance;
        qreal mBlueBalance;
        QColor mLightColor;
    };
}

#endif // SETTINGS_H
