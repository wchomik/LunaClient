#ifndef LIGHTMODEL_H
#define LIGHTMODEL_H

#include <memory>

#include <QObject>
#include <QColor>

#include "lightprovider.h"

namespace luna {
    class LightModel : public QObject {
        Q_OBJECT
        Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
        Q_PROPERTY(qreal whiteness READ whiteness WRITE setWhiteness NOTIFY whitenessChanged)
        Q_PROPERTY(bool colorFromTheme READ colorFromTheme WRITE setColorFromTheme NOTIFY colorFromThemeChanged)
    public:
        explicit LightModel(QObject * parent = nullptr);
        void provider(std::weak_ptr<LightProvider> ptr);

        QColor color() const;
        qreal whiteness() const;
        bool colorFromTheme() const;
    public slots:
        void setColor(QColor color);
        void setWhiteness(qreal whiteness);
        void setColorFromTheme(bool colorFromTheme);
    signals:
        void colorChanged(QColor color);
        void whitenessChanged(qreal whiteness);
        void colorFromThemeChanged(bool colorFromTheme);
    private:
        std::weak_ptr<LightProvider> mProvider;
    };
}

#endif // LIGHTMODEL_H
