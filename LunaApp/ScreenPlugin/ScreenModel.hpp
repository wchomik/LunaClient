#pragma once

#include "ScreenProvider.hpp"

#include <luna/interface/Property.hpp>
#include <luna/interface/SettingsGroup.hpp>

#include <QObject>
#include <QSettings>

class ScreenModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int depth READ depth WRITE setDepth NOTIFY depthChanged)
    Q_PROPERTY(qreal brightness READ brightness WRITE setBrightness NOTIFY brightnessChanged)
    Q_PROPERTY(qreal gamma READ gamma WRITE setGamma NOTIFY gammaChanged)
    Q_PROPERTY(qreal blackLevel READ blackLevel WRITE setBlackLevel NOTIFY blackLevelChanged)
    Q_PROPERTY(qreal smoothness READ smoothness WRITE setSmoothness NOTIFY smoothnessChanged)
public:
    explicit ScreenModel();
    ~ScreenModel() override;
    void provider(std::weak_ptr<ScreenProvider> ptr);

    int depth() const { return mDepth; }
    qreal brightness() const { return mBrightness; }
    qreal gamma() const { return mGamma; }
    qreal blackLevel() const { return mBlackLevel; }
    qreal smoothness() const { return mSmoothness; }

public slots:
    void setDepth(int value);
    void setBrightness(qreal value);
    void setGamma(qreal value);
    void setBlackLevel(qreal value);

    void setSmoothness(qreal smoothness);

signals:
    void depthChanged(int value);
    void brightnessChanged(qreal value);
    void gammaChanged(qreal value);
    void blackLevelChanged(qreal value);

    void smoothnessChanged(qreal smoothness);

private:
    void applyDepth();
    void applyBrightness();
    void applyGamma();

    QSettings mSettings;
    luna::interface::SettingsGroup mGroup;
    luna::interface::Property<int> mDepth;
    luna::interface::Property<qreal> mBrightness;
    luna::interface::Property<qreal> mGamma;
    luna::interface::Property<qreal> mBlackLevel;
    luna::interface::Property<qreal> mSmoothness;

    std::weak_ptr<ScreenProvider> mProvider;
};
