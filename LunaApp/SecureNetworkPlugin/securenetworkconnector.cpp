#include "securenetworkconnector.h"

#include <string>
#include <cstdio>
#include <functional>

#include <QDebug>
#include <QString>

#include <lunacore/colorutils.h>

#include <tls/standard_timer.hpp>

#include "command_dispatcher.h"

using namespace std::chrono_literals;
using namespace luna;

static void my_debug( void *ctx, int level,
                      const char *file, int line,
                      const char *str )
{
    qDebug() << file << line << str;
}

SecureNetworkConnector::SecureNetworkConnector() :
    mDiscovery([this](const net::Address & address) { handleHostDiscovered(address); }, 5000ms)
{
    mRandom.seed(&mEntropy, "Some entropy", 6);

    mCaCertificate.parse_file("ca.crt");
    mOwnCertificate.parse_file("own.crt");
    mOwnPrivateKey.parse_file("own.key", nullptr);

    mCommandConfiguration.set_certifiate_authority_chain(&mCaCertificate);
    mCommandConfiguration.set_own_certificate(&mOwnCertificate, &mOwnPrivateKey);

    mCommandConfiguration.set_defaults(tls::endpoint::client, tls::transport::stream, tls::preset::default_);
    //mCommandConfiguration.set_authentication_mode(tls::authentication_mode::none);
    mCommandConfiguration.set_authentication_mode(tls::authentication_mode::required);
    mCommandConfiguration.set_random_generator(&mRandom);
    mCommandConfiguration.enable_debug(&my_debug, 0);
    //m_ssl.setup(&m_tls_configuration);
}

SecureNetworkConnector::~SecureNetworkConnector() {

}

void SecureNetworkConnector::update() {
    mDiscovery.discover();
    for (auto & host : mHosts) {
        if (host.second->isConnected()) {
            //try {
                host.second->send();
//            } catch (tls::exception const & exception) {
//                qDebug() << exception.what();
//                throw;
//            }
        }
    }
}

void SecureNetworkConnector::getHosts(std::vector<luna::Host *> & hosts) {
    for (auto & host : mHosts) {
        hosts.emplace_back(host.second.get());
    }
}

void SecureNetworkConnector::handleHostDiscovered(const net::Address & address) {
    auto ip = address.toString();
    auto it = mHosts.find(ip);

    // qDebug() << "Found host";
    if (mHosts.end() == it) {
        qDebug() << "Found host and it is new";
        mHosts.emplace(ip, std::make_unique<SecureNetworkHost>(address, *this));
    }
}



SecureNetworkHost::SecureNetworkHost(net::Address address,  SecureNetworkConnector & owner) :
    mOwner(owner),
    mHostIp(address.toString()),
    mIsConnected(false),
    mShouldRun(true),
    mCommandEncoder(&mCommandSSL),
    mEncoder(&mCommandEncoder),
    mDecoder(this)
{
    qDebug() << "Creating host";
    mCommandSSL.setup(&owner.mCommandConfiguration);

    mThread = std::thread([this, address]() {
        this->threadFunction(address);
    });
}

SecureNetworkHost::~SecureNetworkHost() {
    mShouldRun.store(false);
    mThread.join();
}

std::string SecureNetworkHost::displayName() const {
    return "ASDQWERTYRTYRFDF";
}

void SecureNetworkHost::connect() {

}

void SecureNetworkHost::disconnect() {

}

bool SecureNetworkHost::isConnected() const {
    return mIsConnected;
}

void SecureNetworkHost::getStrands(std::vector<luna::Strand *> & strands) {
    for(auto & s : mStrands) {
        strands.emplace_back(s.strand.get());
    }
}

void SecureNetworkHost::send()
{
    qDebug() << "Sending data";
    constexpr size_t BUFFER_SIZE = 1024 * 2;
    uint8_t buffer[BUFFER_SIZE];
    serializer s(buffer, BUFFER_SIZE);
    for (auto const& data : mStrands) {
        auto & strand = *data.strand;
        Color * pixels = strand.pixels();
        Color error = Color::Zero();
        ColorChannels channels = strand.config().colorChannels;

        int range;
        std::function<void(ColorScalar)> writer;
        switch (data.bitDepth) {
            case bit_depth::integer_8_bits: {
                range = (1 << 8) - 1;
                writer = [&s](ColorScalar value) {
                    s << static_cast<uint8_t>(value);
                };
                break;
            }
            case bit_depth::integer_16_bits: {
                range = (1 << 16) - 1;
                writer = [&s](ColorScalar value) {
                    s << static_cast<uint16_t>(value);
                };
                break;
            }
            default: throw std::out_of_range("Enum value out of range");
        }

        size_t const pixelCount = strand.config().count;
        auto && d = qDebug();
        for (size_t i = 0; i < pixelCount; ++i){
            Color corrected = pixels[i] * range + error;
            Color clampedRounded = corrected.array().max(0).min(range).round().matrix();
            error = corrected - clampedRounded;

            for (int j = 0; j< 4; ++j) {
                if (0 != ((1 << j) & channels)) {
                    //d << corrected(j);
                    writer(clampedRounded(j));
                }
            }
        }
    }

    if (s.size() > 0) {
        qDebug() << "Sending" << s.size() << "bytes";
        dataSsl.write(s.data(), s.size());
    }
}

void SecureNetworkHost::configuration_received(luna_configuration const & configuration)
{
    qDebug() << "Config received";
    for (auto const & s : configuration.strands) {
        luna::Strand::Config config;
        config.count = s.count;
        config.begin << s.begin.x, s.begin.y, s.begin.z;
        config.end << s.end.x, s.end.y, s.end.z;
        config.colorSpace = luna::ColorSpace::ws2812(); // TODO
        config.colorChannels = static_cast<luna::ColorChannels>(s.colorChannels);
        StrandData data = {
            std::make_unique<luna::Strand>(config),
            s.pixel_bit_depth
        };
        mStrands.emplace_back(std::move(data));
    }

    mEncoder.open_data_channel();
}

void SecureNetworkHost::data_channel_opened(data_channel_configuration const & channel)
{
    qDebug() << "Data channel opened";
    random.seed(&entropy,
        reinterpret_cast<char const *>(channel.shared_key.data()),
        channel.shared_key.size());
    dataConfig.set_random_generator(&random);

    char const identity[] = "Luna";
    dataConfig.set_shared_key(channel.shared_key.data(),
        channel.shared_key.size(),
        reinterpret_cast<uint8_t const*>(identity),
        sizeof(identity));

    dataConfig.set_defaults(tls::endpoint::client, tls::transport::datagram, tls::preset::default_);

    auto port = std::to_string(channel.port);
    qDebug() << "Connect to" << mHostIp.c_str() << ":" << port.c_str();
    socket.connect(mHostIp.c_str(), port.c_str(), tls::protocol::udp);

    dataSsl.setup(&dataConfig);
    dataSsl.set_input_output(&socket);
    dataSsl.set_timer(&timer);
    qDebug() << "Handshaking DTLS";
    dataSsl.handshake();
    qDebug() << "Handshake done";

    mIsConnected = true;
}

void SecureNetworkHost::data_channel_closed()
{
    mIsConnected = false;
}

void SecureNetworkHost::threadFunction(net::Address address)
{
    qDebug() << "Starting host thread";

    auto ip = address.toString();
    auto port = std::to_string(static_cast<int>(address.port()));
    mCommandSocket.connect(ip.c_str(), port.c_str(), tls::protocol::tcp);
    qDebug() << "Connected socket to" << ip.c_str();

    mCommandSSL.set_input_output(&mCommandSocket);

    if (mCommandSSL.handshake()) {
        qDebug() << "Handshake successful";
        command_dispatcher dispatcher(&mDecoder);

        mEncoder.request_configuration();

        while (mShouldRun.load()) {
            uint8_t buffer[128];
            auto size = mCommandSSL.read(buffer, sizeof(buffer));
            dispatcher.dispatch(buffer, static_cast<size_t>(size));
            std::this_thread::sleep_for(100ms);
        }
    } else {
        qDebug() << "Handshake failed";
    }
}
