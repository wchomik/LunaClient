#ifndef LUNAMANAGER_H
#define LUNAMANAGER_H

#include <memory>

#include <QObject>
#include <QTimer>
#include <QMutex>

#include <Eigen/Core>
#include "colorutils.h"
#include "colormode.h"
#include "colorspace.h"

#include "providerfactory.h"
#include "config.h"

namespace luna {
    class Manager : public QObject
    {
        Q_OBJECT
    public:
        explicit Manager(QObject * parent = 0);
        ~Manager();
        Manager(const Manager &) = delete;
        Manager & operator=(const Manager &) = delete;

        Provider * currentProvider();
    public slots:
        void setWhiteBalance(const Color & color);
        void setMode(luna::ProviderType type);
    private slots:
        void onDataReady();
        void onConnected();
        void onDisconnected();
    private:
        void updateColorMode();
        void activateProvider();
        void deactivateProvider();

        // color management
        Color mWhiteBalance;
        ColorSpace mSourceColorSpace;
        ColorSpace mDestinationColorSpace;
        ColorMode mCurrentColorMode;
        std::unique_ptr<class ColorProcessor> mColorProcessor;

        // connection management
        class Connection * mLuna;
        QTimer mConnectionTimer;

        // provider management
        ProviderFactory mProviderFactory;
        ProviderType mCurrentProviderType;
        std::unique_ptr<class Provider> mActiveProvider;
        Config mLunaConfig;

        QMutex mMutex;
    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    };
}

#endif // LUNAMANAGER_H
