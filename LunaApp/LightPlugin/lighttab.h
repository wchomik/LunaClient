#ifndef LIGHTTAB_H
#define LIGHTTAB_H

#include <QObject>
#include <lunatab.h>

#include "lightmodel.h"

class LightTab : public luna::Tab
{
public:
    LightTab();
    ~LightTab();

    void activate(luna::Manager * manager) override;
    void deactivate(luna::Manager * manager) override;
    QString displayName() const override;
    int displayOrder() const override;
    QObject * model() override;
    QUrl itemUrl() const override;
private:
    std::unique_ptr<LightModel> mModel;
};


#endif // LIGHTTAB_H
