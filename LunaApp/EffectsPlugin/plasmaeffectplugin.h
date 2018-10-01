#ifndef PLASMAEFFECTPLUGIN_H
#define PLASMAEFFECTPLUGIN_H

#include <lunaplugin/effectplugin.h>

#include "plasmamodel.h"

class PlasmaEffectPlugin : public lunacore::EffectPlugin
{
public:
    PlasmaEffectPlugin();
    QString displayName() const override;
    int displayOrder() const override;
    QUrl itemUrl() const override;
    QObject *model() override;
    std::shared_ptr<lunacore::Provider> createProvider() override;
private:
    std::unique_ptr<PlasmaModel> mModel;
};

#endif // PLASMAEFFECTPLUGIN_H
