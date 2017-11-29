#include "lightmodel.h"

#include <QDebug>

using namespace luna;

static const QString whitenessSettingName("whiteness");
static const QString colorSettingName("color");
static const QString themeColorSettingName("themeColor");

LightModel::LightModel(QObject * parent) :
    QObject(parent),
    mSettings()
{
    mSettings.beginGroup("Light");

    mColor = mSettings.value(colorSettingName, QColor(1.0, 1.0, 1.0, 1.0)).value<QColor>();
    mWhiteness = mSettings.value(whitenessSettingName, 0.1).toReal();
    mThemeColor = mSettings.value(themeColorSettingName, false).toBool();

}

LightModel::~LightModel() {
    mSettings.setValue(colorSettingName, mColor);
    mSettings.setValue(whitenessSettingName, mWhiteness);
    mSettings.setValue(themeColorSettingName, mThemeColor);
}

void LightModel::provider(std::weak_ptr<LightProvider> ptr) {
    mProvider = ptr;
    if (auto p = mProvider.lock()) {
        p->color(qColorToColor(mColor));
        p->whiteness(static_cast<luna::ColorScalar>(mWhiteness));
        p->shouldGetColorFromTheme(mThemeColor);
    }
}

QColor LightModel::color() const {
    return mColor;
}

void LightModel::setColor(QColor value) {
    if (mColor == value) {
        return;
    }

    mColor = value;
    if (auto p = mProvider.lock()) {
        p->color(qColorToColor(value));
    }
    colorChanged(value);
}

qreal LightModel::whiteness() const {
    return mWhiteness;
}

void LightModel::setWhiteness(qreal value) {
    if (mWhiteness == value) {
        return;
    }

    mWhiteness = value;
    if (auto p = mProvider.lock()) {
        p->whiteness(static_cast<luna::ColorScalar>(value));
    }
    whitenessChanged(value);
}


bool LightModel::themeColor() const {
    return mThemeColor;
}

void LightModel::setThemeColor(bool value) {
    if (mThemeColor == value) {
        return;
    }

    mThemeColor = value;
    if (auto p = mProvider.lock()) {
        p->shouldGetColorFromTheme(value);
    }
    themeColorChanged(value);
}
