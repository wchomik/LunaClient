#include "securehost.h"

#include <lunacore/strand.h>
#include <luna/ByteStream.hpp>

#include <QDebug>

#include <array>
#include <algorithm>

SecureHost::SecureHost(QHostAddress hostAddress) :
    mAddress(hostAddress),
    mControlSocket(std::make_unique<ControlSocket>(hostAddress, 9510, static_cast<luna::client::Listener *>(this))),
    mConnected(false)
{
}

SecureHost::~SecureHost() = default;

QHostAddress SecureHost::address() const noexcept
{
    return mAddress;
}

void SecureHost::send()
{
    constexpr size_t BUFFER_SIZE = 1024 * 2;
    uint8_t buffer[BUFFER_SIZE];
    luna::ByteStream s(buffer, BUFFER_SIZE);

    for (auto const& data : mStrands) {
        auto & strand = *data.strand;

        data.serializer->serialize(strand, s);
    }

    if (s.size() > 0) {
        mDataSocket->write(s.data(), s.size());
    }
}

std::string SecureHost::displayName() const
{
    return "Secure";
}

void SecureHost::connect()
{
}

void SecureHost::disconnect()
{
}

bool SecureHost::isConnected() const
{
    return mConnected;
}

void SecureHost::getStrands(std::vector<lunacore::Strand *> & strands)
{
    for (auto & strand : mStrands) {
        strands.emplace_back(strand.strand.get());
    }
}

void SecureHost::strandConfigurationReceived(const luna::LunaConfiguration &configuration)
{
    for (auto const & strand : configuration.strands) {
        lunacore::Strand::Config config;

        auto const & cs = strand.colorSpace;
        auto conv = [](auto const & coords) {
            qDebug() << coords.u << coords.v;
            return lunacore::cieCoord_t{coords.u, coords.v};
        };

        config.colorSpace = lunacore::ColorSpace(
            conv(cs.white),
            conv(cs.red),
            conv(cs.green),
            conv(cs.blue)
        );

        config.colorChannels = static_cast<lunacore::ColorChannels>(strand.colorChannels);
        config.count = strand.pixelCount;

        auto const & b = strand.begin;
        config.begin = Eigen::Vector3f(b.x, b.y, b.z);

        auto const & e = strand.end;
        config.end = Eigen::Vector3f(e.x, e.y, e.z);

        auto s = std::make_unique<lunacore::Strand>(config);

        auto serializer = [format = strand.bitDepth]() -> std::unique_ptr<StrandSerializer> {
            switch(format) {
            case luna::BitDepth::integer8:
                return std::make_unique<StrandSerializer8Bit>();
            case luna::BitDepth::integer16:
                return std::make_unique<StrandSerializer16Bit>();
            }
            throw 5;
        }();

        mStrands.emplace_back(StrandData{std::move(s), std::move(serializer) });
    }

    mControlSocket->encoder().requestDataChannel();
}

void SecureHost::dataChannelOpened(const luna::DataChannelConfiguration &configuration)
{
    QByteArray key(reinterpret_cast<char const *>(configuration.sharedKey.data()),
        static_cast<int>(configuration.sharedKey.size()));

    mDataSocket = std::make_unique<DtlsSocket>(mControlSocket->peerAddress(), configuration.port, key);
    mConnected = true;
}
