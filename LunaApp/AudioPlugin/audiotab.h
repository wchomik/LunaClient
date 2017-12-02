#ifndef AUDIOTAB_H
#define AUDIOTAB_H

#include <QObject>
#include <lunatab.h>

#include "audiomodel.h"

class AudioTab : public luna::Tab
{
public:
    void activate(luna::Manager * manager) override;
    void deactivate(luna::Manager * manager) override;
    QString displayName() const override;
    int displayOrder() const override;
    QUrl itemUrl() const override;
    QObject * model() override;
private:
    std::unique_ptr<AudioModel> mModel;
};

#endif // AUDIOTAB_H
