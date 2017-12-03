#ifndef SCREENEFFECTPLUGIN_H
#define SCREENEFFECTPLUGIN_H

#include <effectplugin.h>

#include "screenmodel.h"

class ScreenEffectPlugin : public luna::EffectPlugin
{
public:
    ScreenEffectPlugin();
    std::shared_ptr<luna::Provider> createProvider() override;
    QString displayName() const override;
    int displayOrder() const override;
    QUrl itemUrl() const override;
    QObject * model() override;
private:
    std::unique_ptr<ScreenModel> mModel;
};

#endif // SCREENEFFECTPLUGIN_H
