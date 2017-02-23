#ifndef LUNAMANAGER_H
#define LUNAMANAGER_H

#include <memory>

#include <QObject>
#include <QTimer>

#include <Eigen/Core>
#include "colorutils.h"
#include "colormode.h"
#include "colorprocessor.h"
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

        void setWhiteBalance(const Color & color);
        void setMode(ProviderType type);
    public slots:
        void updateColorMode();

    private slots:
        void onDataReady();
        void onConnected();
        void onDisconnected();
    private:
        void activateProvider();
        void deactivateProvider();
        void setColorMode(ColorMode mode, const class ColorSpace & colorSpace);

        // color management
        Color mWhiteBalance;
        ColorSpace mSourceColorSpace;
        ColorSpace mDestinationColorSpace;
        ColorMode mCurrentColorMode;
        std::unique_ptr<ColorProcessor> mColorProcessor;

        // connection management
        class Connection * mLuna;
        QTimer mConnectionTimer;

        // provider management
        ProviderFactory mProviderFactory;
        ProviderType mCurrentProviderType;
        std::unique_ptr<Provider> mActiveProvider;
        Config mLunaConfig;
    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    };
}

#endif // LUNAMANAGER_H
