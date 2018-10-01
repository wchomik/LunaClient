#ifndef LIGHTEFFECTPLUGIN_H
#define LIGHTEFFECTPLUGIN_H

#include <QObject>
#include <lunaplugin/effectplugin.h>

#include "lightmodel.h"

class LightEffectPlugin : public lunacore::EffectPlugin
{
public:
    LightEffectPlugin();
    ~LightEffectPlugin();

    std::shared_ptr<lunacore::Provider> createProvider() override;
    QString displayName() const override;
    int displayOrder() const override;
    QObject * model() override;
    QUrl itemUrl() const override;
private:
    std::unique_ptr<LightModel> mModel;
};




#endif // LIGHTEFFECTPLUGIN_H
