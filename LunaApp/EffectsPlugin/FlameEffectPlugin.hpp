#pragma once

#include <luna/interface/EffectPlugin.hpp>

#include "FlameModel.hpp"

class FlameEffectPlugin : public luna::interface::EffectPlugin
{
public:
    FlameEffectPlugin();
    std::shared_ptr<luna::interface::Provider> createProvider() override;
    QString displayName() const override;
    int displayOrder() const override;
    QObject * model() override;
    QUrl itemUrl() const override;
private:
    std::unique_ptr<FlameModel> mModel;
};
