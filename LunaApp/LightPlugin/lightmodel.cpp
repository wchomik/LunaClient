#include "lightmodel.h"

#include <QDebug>

namespace luna {
    LightModel::LightModel(QObject * parent) : QObject(parent) {

    }

    void LightModel::provider(std::weak_ptr<luna::LightProvider> ptr) {
        mProvider = ptr;
        setColor(QColor("white"));
    }

    QColor LightModel::color() const {
        if (auto p = mProvider.lock()) {
            return colorToQColor(p->color());
        } else {
            return QColor();
        }
    }

    void LightModel::setColor(QColor value) {
        qDebug() << "Seting color";
        if (auto p = mProvider.lock()) {
            qDebug() << "Yes";
            if (color() == value) {
                return;
            }

            p->color(qColorToColor(value));
            emit colorChanged(value);
        }
    }

    qreal LightModel::whiteness() const {
        if (auto p = mProvider.lock()) {
            return p->whiteness();
        }
        return 0.0;
    }

    void LightModel::setWhiteness(qreal value) {
        if (auto p = mProvider.lock()) {
            if (whiteness() == value) {
                return;
            }

            p->whiteness(value);
            emit whitenessChanged(value);
        }
    }

    bool LightModel::colorFromTheme() const {
        if (auto p = mProvider.lock()) {
            return p->shouldGetColorFromTheme();
        }
        return false;
    }

    void LightModel::setColorFromTheme(bool value) {
        if (auto p = mProvider.lock()) {
            if (colorFromTheme() == value) {
                return;
            }

            p->shouldGetColorFromTheme(value);
            emit colorFromThemeChanged(value);
        }
    }
}
