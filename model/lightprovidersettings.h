#ifndef LIGHTPROVIDERSETTINGS_H
#define LIGHTPROVIDERSETTINGS_H

#include "providersettings.h"

#include <QColor>

namespace luna {
    class IlluminationProvider;
}


namespace model {
    class LightProviderSettings : public ProviderSettings
    {
        Q_OBJECT
        Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
        Q_PROPERTY(qreal whiteness READ whiteness WRITE setWhiteness NOTIFY whitenessChanged)
    public:
        LightProviderSettings(QObject * parent);
        ~LightProviderSettings();
        void setProvider(luna::Provider *provider) override;
        void setSettings(QSettings *settings) override;

        QColor color(){ return mColor; }
        void setColor(const QColor & value);

        qreal whiteness(){ return mWhiteness; }
        void setWhiteness(const qreal value);
    signals:
        void colorChanged();
        void whitenessChanged();
    private:
        void applyColor();
        void applyWhiteness();

        luna::IlluminationProvider * mProvider;

        QColor mColor;
        qreal mWhiteness;
    };
}

#endif // LIGHTPROVIDERSETTINGS_H
