#ifndef LIGHTPROVIDERSETTINGS_H
#define LIGHTPROVIDERSETTINGS_H

#include "providersettings.h"

#include <QColor>

namespace luna {
    class LightProvider;
}


namespace model {
    class LightProviderSettings : public ProviderSettings
    {
        Q_OBJECT
        Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
        Q_PROPERTY(qreal whiteness READ whiteness WRITE setWhiteness NOTIFY whitenessChanged)
        Q_PROPERTY(bool colorFromTheme READ colorFromTheme WRITE setColorFromTheme NOTIFY colorFromThemeChanged)
    public:
        LightProviderSettings(QObject * parent);
        ~LightProviderSettings();
        void setProvider(luna::Provider *provider) override;
        void setSettings(QSettings *settings) override;

        QColor color(){ return mColor; }
        void setColor(const QColor & value);

        qreal whiteness(){ return mWhiteness; }
        void setWhiteness(const qreal value);

        bool colorFromTheme() { return mColorFromTheme; }
        void setColorFromTheme(const bool value);
    signals:
        void colorChanged();
        void whitenessChanged();
        void colorFromThemeChanged();
    private:
        void applyColor();
        void applyWhiteness();
        void applyColorFromTheme();

        luna::LightProvider * mProvider;

        QColor mColor;
        qreal mWhiteness;
        bool mColorFromTheme;
    };
}

#endif // LIGHTPROVIDERSETTINGS_H
