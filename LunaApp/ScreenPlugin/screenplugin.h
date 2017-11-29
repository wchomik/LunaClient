#ifndef SCREENPLUGIN_H
#define SCREENPLUGIN_H

#include <QObject>
#include <lunaplugin.h>
#include "screenmodel.h"

class ScreenPlugin : public QObject, public luna::LunaPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.luna.screen")
    Q_INTERFACES(luna::LunaPlugin)
public:
    ScreenPlugin();
    virtual ~ScreenPlugin();

    QString name() const override;
    std::shared_ptr<luna::Provider> createProvider() override;
    QObject * model() override;
    int displayOrder() const override;
protected:
    QUrl itemUrl() override;
private:
    std::unique_ptr<ScreenModel> mModel;
};

#endif // SCREENPLUGIN_H
