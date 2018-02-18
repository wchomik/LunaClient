#ifndef NETWORKINTERFACE_H
#define NETWORKINTERFACE_H

#include <vector>

#include "address.h"

namespace net {
    class NetworkInterface
    {
    public:
        const Address & broadcast() const { return m_broadcast; }

        static std::vector<NetworkInterface> list();
    private:
        Address m_broadcast;
    };
}

#endif // NETWORINTERFACE_H
