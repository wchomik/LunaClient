#ifndef SCREENPROVIDERSETTINGS_H
#define SCREENPROVIDERSETTINGS_H

#include "providersettings.h"

#include "../luna/screenprovider.h"

namespace model {
    class ScreenProviderSettings : public ProviderSettings
    {
        Q_OBJECT
        Q_PROPERTY(qreal depth READ depth WRITE setDepth NOTIFY depthChanged)
        Q_PROPERTY(qreal brightness READ brightness WRITE setBrightness NOTIFY brightnessChanged)
        Q_PROPERTY(qreal gamma READ gamma WRITE setGamma NOTIFY gammaChanged)
    public:
        ScreenProviderSettings(QObject * parent = nullptr);
        ~ScreenProviderSettings();
        void setProvider(luna::Provider *provider) override;
        void setSettings(QSettings *settings) override;

        qreal depth() const { return mDepth; }
        qreal brightness() const { return mBrightness; }
        qreal gamma() const { return mGamma; }

        void setDepth(const qreal value);
        void setBrightness(const qreal value);
        void setGamma(const qreal value);
    signals:
        void depthChanged();
        void brightnessChanged();
        void gammaChanged();
    private:
        void applyDepth();
        void applyBrightness();
        void applyGamma();

        qreal mDepth;
        qreal mBrightness;
        qreal mGamma;

        luna::ScreenProvider * mProvider;
    };
}

#endif // SCREENPROVIDERSETTINGS_H
