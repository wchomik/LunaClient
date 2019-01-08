#pragma once

#include <QString>
#include <QUrl>
#include <QObject>

namespace luna::interface {
    class Configurable
    {
    public:
        virtual ~Configurable() = default;
        virtual QString displayName() const = 0;
        virtual int displayOrder() const = 0;
        virtual QUrl itemUrl() const = 0;
        virtual QObject * model() = 0;
    };
}
