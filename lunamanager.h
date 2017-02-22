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

#include "lunaproviderfactory.h"
#include "lunaconfig.h"

namespace luna {

    class LunaManager : public QObject
    {
        Q_OBJECT
    public:
        explicit LunaManager(QObject * parent = 0);
        ~LunaManager();

        void setWhiteBalance(const Color & color);
        void setMode(LunaProviderType type);
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
        class Luna * mLuna;
        QTimer mConnectionTimer;

        // pprovider management
        LunaProviderFactory mProviderFactory;
        LunaProviderType mCurrentProviderType;
        std::unique_ptr<LunaProvider> mActiveProvider;
        LunaConfig mLunaConfig;
    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    };
}

#endif // LUNAMANAGER_H
