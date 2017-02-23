#ifndef LUNA_H
#define LUNA_H

#include <QObject>
#include "colorutils.h"
#include "config.h"

namespace luna {
    class Connection : public QObject
    {
        Q_OBJECT
    public:
        explicit Connection(QObject * parent = nullptr);
        virtual ~Connection();
        virtual bool isConnected() = 0;
        virtual void update(const std::vector<PixelStrand> & pixelStrands,
                            const std::vector<ColorScalar> & whiteStrands) = 0;

        virtual void getConfig(struct Config * config) = 0;
    public slots:
        virtual void connect() = 0;
        virtual void disconnect() = 0;
        virtual void shutdown() = 0;
    signals:
        void connected();
        void disconnected();
    };
}
#endif // LUNA_H
