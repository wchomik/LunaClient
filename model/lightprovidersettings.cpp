#include "lightprovidersettings.h"

#include "../luna/illuminationprovider.h"

namespace model {
    LightProviderSettings::LightProviderSettings(QObject *parent) :
        ProviderSettings(parent),
        mProvider(nullptr)
    {}

    LightProviderSettings::~LightProviderSettings()
    {
        mSettings->setValue("light/color", mColor);
        mSettings->setValue("light/whiteness", mWhiteness);
    }

    void LightProviderSettings::setProvider(luna::Provider * provider)
    {
        mProvider = dynamic_cast<luna::IlluminationProvider *>(provider);
        applyColor();
        applyWhiteness();
    }

    void LightProviderSettings::setColor(const QColor &value)
    {
        if(value != mColor){
            mColor = value;
            applyColor();
            colorChanged();
        }
    }

    void LightProviderSettings::setWhiteness(const qreal value)
    {
        if(value != mWhiteness){
            mWhiteness = value;
            applyWhiteness();
            whitenessChanged();
        }
    }

    void LightProviderSettings::applyColor()
    {
        if(mProvider){
            luna::Color c(
                static_cast<luna::ColorScalar>(mColor.redF()),
                static_cast<luna::ColorScalar>(mColor.greenF()),
                static_cast<luna::ColorScalar>(mColor.blueF()),
                0);
            mProvider->color(c);
        }
    }

    void LightProviderSettings::applyWhiteness()
    {
        if(mProvider)
            mProvider->whiteness(static_cast<luna::ColorScalar>(mWhiteness));
    }

    void LightProviderSettings::setSettings(QSettings *settings)
    {
        ProviderSettings::setSettings(settings);
        mColor = mSettings->value("light/color", QColor(Qt::GlobalColor::white)).value<QColor>();
        mWhiteness = mSettings->value("light/whiteness", 0).toReal();
    }
}


