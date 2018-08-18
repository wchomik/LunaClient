#pragma once

#include <lunacore/connector.h>
#include <lunacore/colorutils.h>
#include <lunacore/strand.h>

#include "hostdiscovery.h"

#include <chrono>
#include <thread>
#include <map>
#include <atomic>

#include <tls/certificate.hpp>
#include <tls/private_key.hpp>
#include <tls/ssl.hpp>
#include <tls/configuration.hpp>
#include <tls/counter_deterministic_random_generator.hpp>
#include <tls/standard_entropy.hpp>
#include <tls/standard_timer.hpp>
#include <tls/socket_input_output.hpp>

#include "client_handler.h"
#include "client_encoder.h"
#include "command_encoder.h"
#include "client_command_decoder.h"

class SecureNetworkConnector;

class SecureNetworkHost : public luna::Host, private client_handler {
public:
    SecureNetworkHost(net::Address address, SecureNetworkConnector & owner);
    ~SecureNetworkHost() override;
    std::string displayName() const override;
    void connect() override;
    void disconnect() override;
    bool isConnected() const override;
    void getStrands(std::vector<luna::Strand *> &strands) override;
    void send();
private:
    virtual void configuration_received(luna_configuration const & luna_configuration) override;
    virtual void data_channel_opened(data_channel_configuration const & channel) override;
    virtual void data_channel_closed() override;

    void threadFunction(net::Address address);

    struct StrandData {
        std::unique_ptr<luna::Strand> strand;
        bit_depth bitDepth;
    };

    SecureNetworkConnector & mOwner;
    std::string mHostIp;
    bool mIsConnected;
    std::vector<StrandData> mStrands;

    std::thread mThread;
    std::atomic<bool> mShouldRun;

    tls::socket_input_output mCommandSocket;
    tls::ssl mCommandSSL;

    tls::standard_entropy entropy;
    tls::counter_deterministic_random_generator random;
    tls::configuration dataConfig;
    tls::socket_input_output socket;
    tls::ssl dataSsl;
    tls::standard_timer timer;

    command_encoder mCommandEncoder;
    client_encoder mEncoder;
    client_command_decoder mDecoder;
};

class SecureNetworkConnector : public luna::Connector
{
public:
    SecureNetworkConnector();
    SecureNetworkConnector(const SecureNetworkHost &) = delete;
    ~SecureNetworkConnector() override;
    SecureNetworkConnector & operator=(const SecureNetworkHost &) = delete;
    void update() override;
    void getHosts(std::vector<luna::Host *> & hosts) override;
private:
    void updateHosts();
    void onHostConnected();
    void handleHostDiscovered(const net::Address & address);

    std::map<std::string, std::unique_ptr<SecureNetworkHost>> mHosts;

    HostDiscovery mDiscovery;

    tls::certificate mCaCertificate;
    tls::certificate mOwnCertificate;
    tls::private_key mOwnPrivateKey;
    tls::configuration mCommandConfiguration;
    tls::counter_deterministic_random_generator mRandom;
    tls::standard_entropy mEntropy;

    friend class SecureNetworkHost;
};
