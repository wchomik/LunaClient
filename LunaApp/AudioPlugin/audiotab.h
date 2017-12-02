#ifndef AUDIOPLUGIN_H
#define AUDIOPLUGIN_H

#include <QObject>
#include <lunaplugin.h>

#include "audiomodel.h"

class AudioPlugin : public QObject, public luna::LunaPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.luna.audio")
    Q_INTERFACES(luna::LunaPlugin)
public:
    AudioPlugin();
    virtual ~AudioPlugin();

    QString name() const override;
    std::shared_ptr<luna::Provider> createProvider() override;
    QObject * model() override;
    int displayOrder() const override;
protected:
    QUrl itemUrl() override;
private:
    std::unique_ptr<AudioModel> mModel;
};

#endif // AUDIOPLUGIN_H
