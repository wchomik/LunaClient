#ifndef PLASMAEFFECTPLUGIN_H
#define PLASMAEFFECTPLUGIN_H

#include <luna/interface/effectplugin.h>

#include "plasmamodel.h"

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

#endif // PLASMAEFFECTPLUGIN_H
