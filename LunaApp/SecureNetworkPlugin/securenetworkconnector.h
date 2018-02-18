#ifndef SECURENETWORKCONNECTOR_H
#define SECURENETWORKCONNECTOR_H

#include <lunacore/connector.h>
#include <lunacore/colorutils.h>
#include <lunacore/strand.h>

class SecureNetworkHost : public luna::Host {
public:
    HostUDPLegacy(net::Address address);
    virtual ~HostUDPLegacy();
    std::string displayName() const override;
    void connect() override;
    void disconnect() override;
    bool isConnected() const override;
    void getStrands(std::vector<luna::Strand *> &strands) override;
    void send();
    const net::Address & address() const { return mAddress; }
private:
    bool mIsConnected;
    std::vector<std::unique_ptr<luna::Strand>> mStrands;

    BinaryStream mBuffer;
};

class SecureNetworkConnector : public luna::Connector
{
public:
    ConnectorUDPLegacy(uint16_t port);
    ConnectorUDPLegacy(const ConnectorUDPLegacy &) = delete;
    virtual ~ConnectorUDPLegacy();
    ConnectorUDPLegacy & operator=(const ConnectorUDPLegacy &) = delete;
    void update() override;
    void getHosts(std::vector<luna::Host *> & hosts) override;
private:
    void sendDiscovery();
    void receiveFromHosts();
    void updateHosts();
    void onHostConnected();

    std::vector<net::NetworkInterface> mInterfaces;
    net::SocketUdp mSocket;
    uint16_t mPort;
    std::chrono::steady_clock::duration mDiscoveryInterval;
    std::chrono::steady_clock::time_point mNextDiscovery;
    std::vector<std::unique_ptr<HostUDPLegacy>> mHosts;
};

#endif // SECURENETWORKCONNECTOR_H
