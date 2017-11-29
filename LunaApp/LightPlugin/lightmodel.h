#ifndef LIGHTMODEL_H
#define LIGHTMODEL_H

#include <memory>

#include <QObject>
#include <QColor>
#include <QSettings>

#include "lightprovider.h"

class LightModel : public QObject {
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(qreal whiteness READ whiteness WRITE setWhiteness NOTIFY whitenessChanged)
    Q_PROPERTY(bool themeColor READ themeColor WRITE setThemeColor NOTIFY themeColorChanged)
public:
    explicit LightModel(QObject * parent = nullptr);
    ~LightModel();
    void provider(std::weak_ptr<LightProvider> ptr);

    QColor color() const;
    qreal whiteness() const;
    bool themeColor() const;
public slots:
    void setColor(QColor color);
    void setWhiteness(qreal whiteness);
    void setThemeColor(bool colorFromTheme);
signals:
    void colorChanged(QColor color);
    void whitenessChanged(qreal whiteness);
    void themeColorChanged(bool colorFromTheme);
private:
    QColor mColor;
    qreal mWhiteness;
    bool mThemeColor;

    std::weak_ptr<LightProvider> mProvider;
    QSettings mSettings;
};


#endif // LIGHTMODEL_H
