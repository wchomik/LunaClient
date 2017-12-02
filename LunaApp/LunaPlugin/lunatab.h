#ifndef LUNATAB_H
#define LUNATAB_H

#include <QString>
#include <QUrl>
#include <QObject>


namespace luna {
    class Luna;

    class Tab
    {
    public:
        virtual ~Tab();
        virtual void activate(Luna * application) = 0;
        virtual void deactivate(Luna * application) = 0;
        virtual QString displayName() const = 0;
        virtual int displayOrder() const = 0;
        virtual QUrl itemUrl() const = 0;
        virtual QObject * model() = 0;
    };
}

#endif // LUNATAB_H
