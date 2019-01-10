#ifndef AUDIOEFFECTPLUGIN_H
#define AUDIOEFFECTPLUGIN_H

#include <QObject>
#include <luna/interface/effectplugin.h>

#include "audiomodel.h"

class AudioEffectPlugin : public luna::interface::EffectPlugin
{
public:
    std::shared_ptr<luna::interface::Provider> createProvider() override;
    QString displayName() const override;
    int displayOrder() const override;
    QUrl itemUrl() const override;
    QObject * model() override;
private:
    std::unique_ptr<AudioModel> mModel;
};

#endif // AUDIOEFFECTPLUGIN_H
