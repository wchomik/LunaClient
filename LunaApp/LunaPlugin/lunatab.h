#ifndef LUNATAB_H
#define LUNATAB_H

#include <QString>
#include <QUrl>
#include <QObject>


namespace luna {
    class Tab
    {
    public:
        virtual ~Tab();
        virtual void enabled(bool state) = 0;
        virtual QString displayName() = 0;
        virtual int displayOrder() = 0;
        virtual QUrl itemUrl() = 0;
        virtual QObject * model() = 0;


    };
}

#endif // LUNATAB_H
