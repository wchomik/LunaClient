#include "connectorudplegacy.h"

#include <cstdint>
#include <limits>
#include <algorithm>
#include <qdebug.h>

namespace luna {
    using namespace std::chrono_literals;

    HostUDPLegacy::HostUDPLegacy(net::Address address) :
        mIsConnected(false),
        mAddress(address),
        mBuffer(BUFFER_SIZE)
    {
        Strand::Config conf;
        conf.colorSpace = ColorSpace::ws2812();
        conf.whiteBalance << 0.9f, 1.0f, 0.45f, 1.0f;

        conf.begin << -1, -1, 0;
        conf.end << -1, 1, 0;
        conf.colorChannels = ColorChannels::white;
        conf.count = 1;
        mStrands.emplace_back(std::make_unique<Strand>(conf));

        conf.begin << 1, -1, 0;
        conf.end << 1, 1, 0;
        conf.colorChannels = ColorChannels::white;
        conf.count = 1;
        mStrands.emplace_back(std::make_unique<Strand>(conf));

        conf.begin << -1, -1.4f, 0;
        conf.end << -1, 1, 0;
        conf.colorChannels = ColorChannels::rgb;
        conf.count = PIXEL_COUNT;
        mStrands.emplace_back(std::make_unique<Strand>(conf));

        conf.begin << 1, -1.4f, 0;
        conf.end << 1, 1, 0;
        conf.colorChannels = ColorChannels::rgb;
        conf.count = PIXEL_COUNT;
        mStrands.emplace_back(std::make_unique<Strand>(conf));


        mSocket.setNonBlock(true);
        address.setPort(1234);
        mSocket.connect(address);

        mSocket.bind(address);
    }

    HostUDPLegacy::~HostUDPLegacy() {
        mSocket.setNonBlock(false);
        if (isConnected()) {
            disconnect();
        }
    }

    std::string HostUDPLegacy::displayName() const {
        return "Legacy Raspberry Pi Luna";
    }

    void HostUDPLegacy::connect() {
        net::Address any(net::Address::LOOPBACK, 1234);
        mSocket.bind(any);
        mBuffer.reset();
        mBuffer << static_cast<uint8_t>(101);
        mBuffer << static_cast<uint8_t>(1);
        mSocket.send(mBuffer);
        mIsConnected = true;
    }

    void HostUDPLegacy::disconnect() {
        mBuffer.reset();
        mBuffer << static_cast<uint8_t>(99);
        mSocket.send(mBuffer);
    }

    bool HostUDPLegacy::isConnected() const {
        return mIsConnected;
    }

    void HostUDPLegacy::getStrands(std::vector<Strand *> & strands) {
        for (auto && strand : mStrands) {
            strands.emplace_back(strand.get());
        }
    }

    void HostUDPLegacy::send() {
        mBuffer.reset();
        mBuffer << static_cast<uint8_t>(101);
        mBuffer << static_cast<uint8_t>(61);
        for (size_t i = 0; i < 2; ++i){
            ColorScalar brightness = mStrands[i]->pixels()[0][3];
            brightness = std::max<ColorScalar>(0.0, std::min<ColorScalar>(1.0, brightness));
            uint16_t value = static_cast<uint16_t>(std::numeric_limits<uint16_t>::max() * brightness);
            mBuffer << value;
        }
        for (size_t i = 2; i < 4; ++i){
            Color * strand = mStrands[i]->pixels();
            Color error = Color::Zero();
            for (int j = 0; j < PIXEL_COUNT; ++j){
                Color corrected = strand[j] * 255 + error;
                Color clampedRounded = corrected.array().max(0).min(255).round().matrix();
                error = corrected - clampedRounded;
                Eigen::Matrix<uint8_t, 4, 1> rgb = clampedRounded.cast<uint8_t>();
                mBuffer.write(rgb.data(), 3);
            }
        }

        mSocket.send(mBuffer);
    }

    ConnectorUDPLegacy::ConnectorUDPLegacy(uint16_t port) :
        mPort(port)
    {
        mDiscoveryInterval = 500ms;
        mSocket.setBroadcast(true);
        mSocket.setNonBlock(true);
        net::Address any(net::Address::ANY, mPort);
        mSocket.bind(any);

        mNextDiscovery = std::chrono::steady_clock::now();
    }

    ConnectorUDPLegacy::~ConnectorUDPLegacy() {

    }


    void ConnectorUDPLegacy::update() {
        updateHosts();
    }

    static constexpr char helloMessage[] = "\x01LunaDaemon";
    static constexpr int helloLen = sizeof(helloMessage) - 1;

    void ConnectorUDPLegacy::sendDiscovery() {
        auto now = std::chrono::steady_clock::now();
        if((mHosts.size() == 0) && (mNextDiscovery < now)) {
            mNextDiscovery = now + mDiscoveryInterval;
            net::Address broadcast(net::Address::BROADCAST, mPort);
            mSocket.sendTo(helloMessage, helloLen, broadcast);
        }
    }

    void ConnectorUDPLegacy::receiveFromHosts() {
        for (;;){
            net::Address from;
            char inbuf[128];
            int len = mSocket.receiveFrom(inbuf, sizeof(inbuf), from);
            if (len < 0) break;

            inbuf[len] = 0;
            if (helloLen != len) {
                auto foundHost = std::find_if(
                    mHosts.begin(),
                    mHosts.end(),
                    [from](const auto & host) { return host->address() == from; });
                bool hostExists = (foundHost != mHosts.end());
                if (!hostExists) {
                    mHosts.push_back(std::make_unique<HostUDPLegacy>(from));}
            }
        }
    }

    void ConnectorUDPLegacy::updateHosts() {
        for (auto && host : mHosts) {
            if (host->isConnected()) {
                host->send();
            } else {
                host->connect();
            }
        }
    }

    void ConnectorUDPLegacy::getHosts(std::vector<Host *> &hosts) {
        sendDiscovery();
        receiveFromHosts();
        for (auto && host : mHosts) {
            hosts.emplace_back(host.get());
        }
    }
}
