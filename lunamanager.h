#ifndef LUNAMANAGER_H
#define LUNAMANAGER_H

#include <QObject>
#include <QTimer>

namespace luna {
    class LunaManager : public QObject
    {
        Q_OBJECT
    public:
        explicit LunaManager(QObject *parent = 0);

    public slots:
        void onShutdown();
    private slots:
        void onDataReady();
        void onConnected();
        void onDisconnected();
    private:
        void setProvider(class LunaProvider * provider);

        QTimer mConnectionTimer;
        class Luna * mLuna;
        class LunaProvider * mProvider;
    };
}

#endif // LUNAMANAGER_H
