#include "lightmodel.h"

#include <QDebug>

using namespace luna;

LightModel::LightModel(QObject * parent) :
    QObject(parent),
    mColor(),
    mWhiteness(0.0),
    mTemperature(5500.0),
    mBrightness(1.0)
{}

LightModel::~LightModel() {
}

void LightModel::provider(std::weak_ptr<LightProvider> ptr) {
    mProvider = ptr;
    setSource(mSource);
}

QColor LightModel::color() const {
    return mColor;
}

void LightModel::setColor(const QColor & value) {
    if (auto p = mProvider.lock()) {
        p->setColor(qColorToColor(value));
    }

    if (mColor != value) {
        mColor = value;
        colorChanged(value);
    }
}

qreal LightModel::whiteness() const {
    return mWhiteness;
}

void LightModel::setWhiteness(qreal value) {
    if (auto p = mProvider.lock()) {
        p->setWhiteness(static_cast<luna::ColorScalar>(value));
    }

    if (mWhiteness != value) {
        mWhiteness = value;
        whitenessChanged(value);
    }
}

qreal LightModel::temperature() const {
    return mTemperature;
}

void LightModel::setTemperature(qreal value) {
    if (auto p = mProvider.lock()) {
        p->setColorFromTemperature(static_cast<luna::ColorScalar>(value));
    }

    if (mTemperature != value) {
        mTemperature = value;
        temperatureChanged(mTemperature);
    }
}

qreal LightModel::brightness() const {
    return mBrightness;
}

void LightModel::setBrightness(qreal value) {
    if (auto p = mProvider.lock()) {
        p->setBrightness(static_cast<luna::ColorScalar>(value));
    }

    if (mBrightness != value) {
        mBrightness = value;
        brightnessChanged(value);
    }
}

int LightModel::source() const {
    return mSource;
}

void LightModel::setSource(int value) {
    if (auto p = mProvider.lock()) {
        auto source = static_cast<LightProvider::Source>(value);
        qDebug() << value;
        p->setSource(source);
        switch (source) {
        case LightProvider::Source::ColorPicker:
            p->setColor(qColorToColor(mColor));
            break;
        case LightProvider::Source::Temperature:
            p->setColorFromTemperature(mTemperature);
            break;
        case LightProvider::Source::Manual:
            p->setColor(qColorToColor(mColor));
            p->setWhiteness(static_cast<ColorScalar>(mWhiteness));
            break;
        case LightProvider::Source::Theme:

            break;
        }
        p->setBrightness(static_cast<ColorScalar>(mBrightness));
    }

    if (mSource != value) {
        sourceChanged(mSource);
        mSource = value;
    }
}


