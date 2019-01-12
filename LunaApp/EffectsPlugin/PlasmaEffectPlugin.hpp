#pragma once

#include "PlasmaModel.hpp"

#include <luna/interface/EffectPlugin.hpp>

class PlasmaEffectPlugin : public luna::interface::EffectPlugin
{
public:
    PlasmaEffectPlugin();
    QString displayName() const override;
    int displayOrder() const override;
    QUrl itemUrl() const override;
    QObject *model() override;
    std::shared_ptr<luna::interface::Provider> createProvider() override;
private:
    std::unique_ptr<PlasmaModel> mModel;
};
