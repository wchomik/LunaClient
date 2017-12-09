#ifndef FLAMEEFFECTPLUGIN_H
#define FLAMEEFFECTPLUGIN_H

#include <QObject>
#include <effectplugin.h>

#include "flamemodel.h"

class FlameEffectPlugin : public luna::EffectPlugin
{
public:
    FlameEffectPlugin();
    std::shared_ptr<luna::Provider> createProvider() override;
    QString displayName() const override;
    int displayOrder() const override;
    QObject * model() override;
    QUrl itemUrl() const override;
private:
    std::unique_ptr<FlameModel> mModel;
};



#endif // FLAMEEFFECTPLUGIN_H
