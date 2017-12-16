#ifndef FLAMEMODEL_H
#define FLAMEMODEL_H

#include <memory>

#include <QObject>
#include <QSettings>

#include "flameprovider.h"

class FlameModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal temperatureLow READ temperatureLow WRITE setTemperatureLow NOTIFY temperatureLowChanged)
    Q_PROPERTY(qreal temperatureHigh READ temperatureHigh WRITE setTemperatureHigh NOTIFY temperatureHighChanged)
    Q_PROPERTY(qreal flickerRate READ flickerRate WRITE setFlickerRate NOTIFY flickerRateChanged)
    Q_PROPERTY(qreal brightness READ brightness WRITE setBrightness NOTIFY brightnessChanged)
public:
    explicit FlameModel(QObject *parent = nullptr);
    ~FlameModel();

    void provider(std::weak_ptr<FlameProvider> value);

    qreal temperatureLow() const;
    qreal temperatureHigh() const;
    qreal flickerRate() const;
    qreal brightness() const;
public slots:
    void setTemperatureLow(qreal value);
    void setTemperatureHigh(qreal temperatureHigh);
    void setFlickerRate(qreal flickerRate);
    void setBrightness(qreal brightness);
signals:
    void temperatureLowChanged(qreal value);
    void temperatureHighChanged(qreal value);
    void flickerRateChanged(qreal value);
    void brightnessChanged(qreal value);

private:
    std::weak_ptr<FlameProvider> mProvider;
    qreal mTemperatureLow;
    qreal mTemperatureHigh;
    qreal mFlickerRate;
    qreal mBrightness;
};

#endif // FLAMEMODEL_H
