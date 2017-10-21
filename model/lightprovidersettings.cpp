#include "lightprovidersettings.h"

#include "../luna/illuminationprovider.h"

namespace model {
    LightProviderSettings::LightProviderSettings(QObject *parent) :
        ProviderSettings(parent),
        mProvider(nullptr),
        mColor(),
        mWhiteness(0),
        mColorFromTheme(false)
    {}

    LightProviderSettings::~LightProviderSettings()
    {
        mSettings->setValue("light/color", mColor);
        mSettings->setValue("light/whiteness", mWhiteness);
        mSettings->setValue("light/colorFromTheme", mColorFromTheme);
    }

    void LightProviderSettings::setProvider(luna::Provider * provider)
    {
        mProvider = dynamic_cast<luna::IlluminationProvider *>(provider);
        applyColor();
        applyWhiteness();
        applyColorFromTheme();
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

    void LightProviderSettings::setColorFromTheme(const bool value)
    {
        if(value != mColorFromTheme){
            mColorFromTheme = value;
            applyColorFromTheme();
        }
    }

    void LightProviderSettings::applyColor()
    {
        if(nullptr != mProvider){
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
        if(nullptr != mProvider)
            mProvider->whiteness(static_cast<luna::ColorScalar>(mWhiteness));
    }

    void LightProviderSettings::applyColorFromTheme()
    {
        if(nullptr != mProvider){
            mProvider->shouldGetColorFromTheme(mColorFromTheme);
        }
    }

    void LightProviderSettings::setSettings(QSettings *settings)
    {
        ProviderSettings::setSettings(settings);
        mColor = mSettings->value("light/color", QColor(Qt::GlobalColor::white)).value<QColor>();
        mWhiteness = mSettings->value("light/whiteness", 0).toReal();
        mColorFromTheme = mSettings->value("light/whiteness", false).toBool();
    }
}


