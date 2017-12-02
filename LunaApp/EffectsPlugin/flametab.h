#ifndef FLAMETAB_H
#define FLAMETAB_H

#include <QObject>
#include <lunatab.h>

//#include "flamemodel.h"

class FlameTab : public luna::Tab
{
public:
    void activate(luna::Manager * manager) override;
    void deactivate(luna::Manager * manager) override;
    QString displayName() const override;
    int displayOrder() const override;
    QObject * model() override;
    QUrl itemUrl() const override;
private:
    //std::unique_ptr<FlameModel> mModel;
};
#endif // FLAMETAB_H
