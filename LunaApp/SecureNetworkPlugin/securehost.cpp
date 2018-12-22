#include "securehost.h"

#include <lunacore/strand.h>
#include <luna/proto/Commands_generated.h>

#include <QDebug>

#include <array>
#include <algorithm>
#include <vector>

SecureHost::SecureHost(QHostAddress hostAddress, luna::proto::Discovery const * properties) :
    mAddress(hostAddress),
    mDataSocket(std::make_unique<DtlsSocket>(hostAddress, properties->port())),
    mConnected(false)
{
    QObject::connect(mDataSocket.get(), &DtlsSocket::connected,
        this, &SecureHost::onConnected);

    auto strands = properties->strands();
    if (nullptr == strands) return;
    for (auto const strand : *strands) {
        lunacore::Strand::Config config;

//        auto const & cs = strand.colorSpace;
//        auto conv = [](auto const & coords) {
//            qDebug() << coords.u << coords.v;
//            return lunacore::cieCoord_t{coords.u, coords.v};
//        };

//        config.colorSpace = lunacore::ColorSpace(
//            conv(cs.white),
//            conv(cs.red),
//            conv(cs.green),
//            conv(cs.blue)
//        );
        config.colorSpace = lunacore::ColorSpace::ws2812();

        config.colorChannels = static_cast<lunacore::ColorChannels>(strand->channels());
        config.count = strand->pixelCount();

        auto const & b = strand->begin();
        config.begin = Eigen::Vector3f(b.x(), b.y(), b.z());

        auto const & e = strand->end();
        config.end = Eigen::Vector3f(e.x(), e.y(), e.z());

        auto s = std::make_unique<lunacore::Strand>(config);

        auto serializer = std::make_unique<StrandSerializerRGB>();

        mStrands.emplace_back(StrandData{std::move(s), std::move(serializer) });
    }
}

SecureHost::~SecureHost() = default;

QHostAddress SecureHost::address() const noexcept
{
    return mAddress;
}

void SecureHost::send()
{
    flatbuffers::FlatBufferBuilder builder(1024);

    using namespace luna::proto;


    std::vector<flatbuffers::Offset<luna::proto::StrandData>> offsets;
    for (int i = 0; i < mStrands.size(); ++i){
        auto & strand = *mStrands[i].strand;

        auto strandData = mStrands[i].serializer->serialize(builder, strand);
        strandData.add_id(i);

        offsets.emplace_back(strandData.Finish());
    }

    auto asd = CreateSetColor(builder, builder.CreateVector(offsets));

    auto qwe = CreateCommand(builder, false, AnyCommand_SetColor, asd.Union());

    builder.Finish(qwe);

    mDataSocket->write(builder.GetBufferPointer(), builder.GetSize());
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

void SecureHost::onConnected(bool value)
{
    qDebug() << "Connected";
    mConnected = true;
}
