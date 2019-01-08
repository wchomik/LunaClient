#pragma once

#include "LightModel.hpp"

#include <luna/interface/EffectPlugin.hpp>

#include <QObject>

class LightEffectPlugin : public luna::interface::EffectPlugin
{
public:
    LightEffectPlugin();
    ~LightEffectPlugin();

    std::shared_ptr<luna::interface::Provider> createProvider() override;
    QString displayName() const override;
    int displayOrder() const override;
    QObject * model() override;
    QUrl itemUrl() const override;
private:
    std::unique_ptr<LightModel> mModel;
};
