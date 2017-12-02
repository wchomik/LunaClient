#ifndef SCREENTAB_H
#define SCREENTAB_H

#include <lunatab.h>

#include "screenmodel.h"

class ScreenTab : public luna::Tab
{
public:
    ScreenTab();

    void activate(luna::Manager * manager) override;
    void deactivate(luna::Manager * manager) override;
    QString displayName() const override;
    int displayOrder() const override;
    QUrl itemUrl() const override;
    QObject * model() override;
private:
    std::unique_ptr<ScreenModel> mModel;
};

#endif // SCREENTAB_H
