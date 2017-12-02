#ifndef LIGHTPLUGIN_H
#define LIGHTPLUGIN_H

#include <QObject>
#include <lunatab.h>

#include "lightmodel.h"

class LightTab : public QObject, public luna::Tab
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.luna.light")
    Q_INTERFACES(luna::LunaPlugin)
public:
    LightTab();
    ~LightTab();

    void activate(luna::Luna *application) override;
    void deactivate(luna::Luna *application) override;
    QString displayName() const override;
    int displayOrder() const override;
    QObject * model() override;
    QUrl itemUrl() const override;
private:
    std::unique_ptr<LightModel> mModel;
};

void LightTab::activate(luna::Luna *application)
{
}

void LightTab::deactivate(luna::Luna *application)
{
}


#endif // LIGHTPLUGIN_H
