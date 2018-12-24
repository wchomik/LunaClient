#include "securehost.h"

#include <lunacore/strand.h>
#include <luna/proto/Commands_generated.h>

#include <QDebug>

#include <array>
#include <algorithm>
#include <vector>


static lunacore::cieCoord_t fromProto(luna::proto::UV const & uv)
{
    return {uv.u(), uv.v()};
}

static lunacore::ColorSpace fromProto(luna::proto::ColorSpace const & cs)
{
    return {
        fromProto(cs.white()),
        fromProto(cs.red()),
        fromProto(cs.green()),
        fromProto(cs.blue())
    };
}

static Eigen::Vector3f fromProto(luna::proto::Point const & p)
{
    return {p.x(), p.y(), p.z()};
}

SecureHost::SecureHost(QHostAddress hostAddress, luna::proto::Discovery const * properties) :
    mAddress(hostAddress),
    mDataSocket(std::make_unique<DtlsSocket>(hostAddress, properties->port())),
    mConnected(false),
    mHeartbeatsSkipped(0),
    mShouldSendAck(false),
    mCommandId(0)
{
    QObject::connect(mDataSocket.get(), &DtlsSocket::connected,
        this, &SecureHost::onConnected);

    QObject::connect(mDataSocket.get(), &DtlsSocket::dataReady,
        this, &SecureHost::onResponse);

    QObject::connect(&mHeartbeat, &QTimer::timeout,
        this, &SecureHost::onHeartbeat);

    auto strands = properties->strands();
    if (nullptr == strands) return;
    for (auto const strand : *strands) {
        lunacore::Strand::Config config;

        config.colorSpace = fromProto(strand->colorSpace());

        config.colorChannels = static_cast<lunacore::ColorChannels>(strand->channels());
        config.count = static_cast<uint32_t>(strand->pixelCount());
        config.begin = fromProto(strand->begin());
        config.end = fromProto(strand->end());

        auto s = std::make_unique<lunacore::Strand>(config);

        auto serializer = std::make_unique<StrandSerializerRGB>();

        mStrands.emplace_back(StrandData{std::move(s), std::move(serializer) });
    }

    mHeartbeat.setInterval(2000);
    mHeartbeat.start();
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
    for (size_t i = 0; i < mStrands.size(); ++i){
        auto & strand = *mStrands[i].strand;

        auto strandData = mStrands[i].serializer->serialize(builder, strand);
        strandData.add_id(i);

        offsets.emplace_back(strandData.Finish());
    }

    auto setColorCommand = CreateSetColor(builder, builder.CreateVector(offsets));

    auto command = CreateCommand(builder, nextAckId(), 0, AnyCommand_SetColor, setColorCommand.Union());

    builder.Finish(command);

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
    if (value) {
        qDebug() << "Connected";
        mConnected = true;
    } else {
        disconnected();
    }
}

void SecureHost::onResponse(QByteArray const & array)
{
    mHeartbeatsSkipped = 0;

    using namespace luna::proto;

    auto command = GetCommand(array.data());
    auto ackId = command->ack();
}

void SecureHost::onHeartbeat()
{
    ++mHeartbeatsSkipped;
    if (mShouldSendAck) {
        flatbuffers::FlatBufferBuilder builder(64);

        auto keepAlive = luna::proto::CreateCommand(builder, nextAckId(), 0);
        builder.Finish(keepAlive);

        mDataSocket->write(builder.GetBufferPointer(), builder.GetSize());
    } else {
        mShouldSendAck = true;
    }

    if (mHeartbeatsSkipped >= 5) {
        disconnected();
    }
}

uint32_t SecureHost::nextAckId()
{
    uint32_t ackId = 0;
    if(mShouldSendAck) {
        ++mCommandId;
        ackId = mCommandId;
        mShouldSendAck = false;
    }
    return ackId;
}
