#ifndef LUNA_H
#define LUNA_H

#include <functional>
#include "colorutils.h"
#include "config.h"

namespace luna {
    class Connection
    {
    public:
        virtual ~Connection(){}
        virtual bool isConnected() = 0;
        virtual void update(const std::vector<PixelStrand> & pixelStrands,
                            const std::vector<ColorScalar> & whiteStrands) = 0;

        virtual void getConfig(struct Config * config) = 0;
        virtual bool connect() = 0;
        virtual void disconnect() = 0;
    };
}
#endif // LUNA_H
