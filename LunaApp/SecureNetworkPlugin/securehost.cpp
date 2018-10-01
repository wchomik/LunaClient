#include "securehost.h"

#include <lunacore/strand.h>

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
        auto & strand = data.strand;
        lunacore::Color * pixels = strand->pixels();
        lunacore::Color error = lunacore::Color::Zero();
        lunacore::ColorChannels channels = strand->config().colorChannels;

        int range;
        std::function<void(luna::ByteStream &, lunacore::ColorScalar)> writer;
        switch (data.bitDepth) {
            case luna::BitDepth::integer8: {
                range = (1 << 8) - 1;
                writer = [](luna::ByteStream & s, lunacore::ColorScalar value) {
                    s << static_cast<uint8_t>(value);
                };
                break;
            }
        case luna::BitDepth::integer16: {
                range = (1 << 16) - 1;
                writer = [](luna::ByteStream & s, lunacore::ColorScalar value) {
                    s << static_cast<uint16_t>(value);
                };
                break;
            }
            default: throw std::out_of_range("Enum value out of range");
        }

        size_t const pixelCount = strand->config().count;
        for (size_t i = 0; i < pixelCount; ++i){
            lunacore::Color corrected = pixels[i] * range + error;
            lunacore::Color clampedRounded = corrected.array().max(0).min(range).round().matrix();
            error = corrected - clampedRounded;

            for (int j = 0; j < 4; ++j) {
                if (0 != ((1 << j) & channels)) {
                    writer(s, clampedRounded(j));
                }
            }
        }
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
        mStrands.emplace_back(StrandData{std::move(s), strand.bitDepth});
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
