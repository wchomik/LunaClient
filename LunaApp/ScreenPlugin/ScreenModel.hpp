#pragma once

#include "ScreenProvider.hpp"

#include <QObject>
#include <QSettings>

class ScreenModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal depth READ depth WRITE setDepth NOTIFY depthChanged)
    Q_PROPERTY(qreal brightness READ brightness WRITE setBrightness NOTIFY brightnessChanged)
    Q_PROPERTY(qreal gamma READ gamma WRITE setGamma NOTIFY gammaChanged)
    Q_PROPERTY(qreal blackLevel READ blackLevel WRITE setBlackLevel NOTIFY blackLevelChanged)
public:
    explicit ScreenModel();
    virtual ~ScreenModel();
    void provider(std::weak_ptr<ScreenProvider> ptr);

    qreal depth() const { return mDepth; }
    qreal brightness() const { return mBrightness; }
    qreal gamma() const { return mGamma; }
    qreal blackLevel() const { return mBlackLevel; }

public slots:
    void setDepth(qreal value);
    void setBrightness(qreal value);
    void setGamma(qreal value);
    void setBlackLevel(qreal value);

signals:
    void depthChanged(qreal value);
    void brightnessChanged(qreal value);
    void gammaChanged(qreal value);
    void blackLevelChanged(qreal value);

private:
    void applyDepth();
    void applyBrightness();
    void applyGamma();

    qreal mDepth;
    qreal mBrightness;
    qreal mGamma;
    qreal mBlackLevel;

    std::weak_ptr<ScreenProvider> mProvider;
    QSettings mSettings;
};
