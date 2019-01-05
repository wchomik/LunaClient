#include "securehost.h"

#include <lunacore/strand.h>
#include <luna/proto/Builder.hpp>
#include <luna/proto/SetColor.hpp>
#include <luna/proto/Command.hpp>

#include <QDebug>

#include <array>
#include <algorithm>
#include <vector>


static lunacore::cieCoord_t fromProto(luna::proto::UV const & uv)
{
    return {uv.u, uv.v};
}

static lunacore::ColorSpace fromProto(luna::proto::ColorSpace const & cs)
{
    return {
        fromProto(cs.white),
        fromProto(cs.red),
        fromProto(cs.green),
        fromProto(cs.blue)
    };
}

static Eigen::Vector3f fromProto(luna::proto::Point const & p)
{
    return {p.x, p.y, p.z};
}

SecureHost::SecureHost(QHostAddress hostAddress, luna::proto::Discovery const * properties) :
    mAddress(hostAddress),
    mDataSocket(std::make_unique<DtlsSocket>(hostAddress, properties->port)),
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

    auto & strands = properties->strands;

    for (auto & strand : strands) {
        lunacore::Strand::Config config;

        config.colorSpace = fromProto(strand.colorSpace);

        config.colorChannels = static_cast<lunacore::ColorChannels>(strand.channels.get());
        config.count = static_cast<uint32_t>(strand.pixelCount);
        config.begin = fromProto(strand.begin);
        config.end = fromProto(strand.end);

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

    uint8_t storage[1024];
    auto builder = luna::proto::Builder(storage);
    auto command = builder.allocate<luna::proto::Command>();
    auto setColorCommand = builder.allocate<luna::proto::SetColor>();
    command->command.set(setColorCommand);

    auto str = builder.allocate<luna::proto::StrandData>(mStrands.size());
    setColorCommand->strands.set(str, mStrands.size());

    for (size_t i = 0; i < mStrands.size(); ++i){
        auto & strand = *mStrands[i].strand;

        mStrands[i].serializer->serialize(builder, str[i], strand);
        str[i].id = i;
    }

    mDataSocket->write(builder.data(), builder.size());
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

    auto command = reinterpret_cast<luna::proto::Command const*>(array.data());
    auto ackId = command->ack.get();
}

void SecureHost::onHeartbeat()
{
    ++mHeartbeatsSkipped;
    if (mShouldSendAck) {
        uint8_t buffer[16];
        luna::proto::Builder builder(buffer);
        auto command = builder.allocate<luna::proto::Command>();
        command->id = nextAckId();
        mDataSocket->write(builder.data(), builder.size());
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
