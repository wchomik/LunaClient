#ifndef LUNAMANAGER_H
#define LUNAMANAGER_H

#include <QObject>
#include <QTimer>

#include "colormode.h"

namespace luna {
    class LunaManager : public QObject
    {
        Q_OBJECT
    public:
        explicit LunaManager(QObject *parent = 0);
        ~LunaManager();

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
        class ColorProcessor * mColorProcessor;
        void setColorMode(ColorMode mode);
    };
}

#endif // LUNAMANAGER_H
