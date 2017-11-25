#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <vector>
#include <memory>
#include <string>
#include "event.h"

namespace luna {
    class Host {
    public:
        virtual ~Host();
        virtual std::string displayName() const = 0;
        virtual void connect() = 0;
        virtual void disconnect() = 0;
        virtual bool isConnected() const = 0;
        virtual void getStrands(std::vector<class Strand *> & strands) = 0;
        Event<void()> connected;
    protected:
    };

    class Connector {
    public:
        virtual ~Connector();
        virtual void update() = 0;
        virtual void getHosts(std::vector<Host *> & hosts) = 0;
        Event<void()> hostsChanged;
    };
}

#endif // CONNECTOR_H
