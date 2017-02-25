#ifndef LUNA_H
#define LUNA_H

#include <memory>
#include <string>
#include "colorutils.h"
#include "config.h"

namespace luna {

    class Host {
    public:
        Host();
        Host(const std::string & name) : mName(name) {}
        virtual ~Host(){}

        const std::string & name(){ return mName; }
    protected:
        std::string mName;
        friend class Connection;
    };

    class Connection
    {
    public:
        virtual ~Connection(){}
        virtual bool isConnected() = 0;

        virtual void sendPixels(const std::vector<PixelStrand> & pixelStrands,
                            const std::vector<ColorScalar> & whiteStrands) = 0;

        virtual void update() = 0;
        virtual const std::vector<std::shared_ptr<Host>> & getHosts() = 0;
        virtual void getConfig(struct Config * config) = 0;
        virtual void connect(const Host * host) = 0;
        virtual void disconnect() = 0;
    };
}
#endif // LUNA_H
