#pragma once

#include "LightProvider.hpp"
#if _WIN32
#include "ThemeColor.hpp"
#endif

#include <luna/interface/SettingsGroup.hpp>
#include <luna/interface/Property.hpp>

#include <QObject>
#include <QColor>
#include <QSettings>

#include <memory>

enum Source {
    ColorPicker,
    Temperature,
    Theme,
};

class LightModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(qreal temperature READ temperature WRITE setTemperature NOTIFY temperatureChanged)
    Q_PROPERTY(qreal brightness READ brightness WRITE setBrightness NOTIFY brightnessChanged)
    Q_PROPERTY(int source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(qreal whiteness READ whiteness WRITE setWhiteness NOTIFY whitenessChanged)

public:
    explicit LightModel();
    ~LightModel() override;
    void provider(std::weak_ptr<LightProvider> ptr);

    QColor color() const;
    qreal temperature() const;
    qreal brightness() const;
    int source() const;
    qreal whiteness() const;

public slots:
    void setColor(const QColor & color);
    void setTemperature(qreal temperature);
    void setBrightness(qreal value);
    void setSource(int value);
    void cieXYZ(qreal x, qreal y, qreal z);
    void setWhiteness(qreal value);

signals:
    void colorChanged(QColor color);
    void temperatureChanged(qreal temperature);
    void brightnessChanged(qreal brightness);
    void sourceChanged(int source);
    void whitenessChanged(qreal whiteness);

private:
    void cieXYZ(prism::CieXYZ);
    void notifyProvider();

    QSettings mSettings;
    luna::interface::SettingsGroup mGroup;
    luna::interface::Property<prism::CieXYZ> mColor;
    luna::interface::Property<qreal> mTemperature;
    luna::interface::Property<qreal> mBrightness;
    luna::interface::Property<qreal> mWhiteness;
    luna::interface::Property<int> mSource;

    std::weak_ptr<LightProvider> mProvider;
#if _WIN32
    ThemeColor mThemeColor;
#endif
};
