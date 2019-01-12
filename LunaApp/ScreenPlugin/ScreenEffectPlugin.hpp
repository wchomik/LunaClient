#pragma once

#include "ScreenModel.hpp"

#include <luna/interface/EffectPlugin.hpp>

class ScreenEffectPlugin : public luna::interface::EffectPlugin
{
public:
    ScreenEffectPlugin();
    std::shared_ptr<luna::interface::Provider> createProvider() override;
    QString displayName() const override;
    int displayOrder() const override;
    QUrl itemUrl() const override;
    QObject * model() override;
private:
    std::unique_ptr<ScreenModel> mModel;
};
