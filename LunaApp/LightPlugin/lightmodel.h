#ifndef LIGHTMODEL_H
#define LIGHTMODEL_H

#include <memory>

#include <QObject>
#include <QColor>
#include <QSettings>

#include "lightprovider.h"

class LightModel : public QObject {
    Q_OBJECT
public:

    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(qreal whiteness READ whiteness WRITE setWhiteness NOTIFY whitenessChanged)

    Q_PROPERTY(qreal temperature READ temperature WRITE setTemperature NOTIFY temperatureChanged)

    Q_PROPERTY(qreal brightness READ brightness WRITE setBrightness NOTIFY brightnessChanged)

    Q_PROPERTY(int source READ source WRITE setSource NOTIFY sourceChanged)

    explicit LightModel(QObject * parent = nullptr);
    ~LightModel();
    void provider(std::weak_ptr<LightProvider> ptr);

    QColor color() const;
    qreal whiteness() const;

    qreal temperature() const;

    qreal brightness() const;

    int source() const;

public slots:
    void setColor(const QColor & color);
    void setWhiteness(qreal whiteness);

    void setTemperature(qreal temperature);

    void setBrightness(qreal value);

    void setSource(int value);

signals:
    void colorChanged(QColor color);
    void whitenessChanged(qreal whiteness);

    void temperatureChanged(qreal temperature);

    void brightnessChanged(qreal brightness);
    void sourceChanged(int source);

private:
    QColor mColor;

    qreal mWhiteness;

    qreal mTemperature;

    qreal mBrightness;

    std::weak_ptr<LightProvider> mProvider;
    int mSource;
};


#endif // LIGHTMODEL_H
