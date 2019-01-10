#include "SecureHost.hpp"

#include <luna/interface/Strand.hpp>
#include <luna/proto/Builder.hpp>
#include <luna/proto/SetColor.hpp>
#include <luna/proto/Command.hpp>

#include <QDebug>

#include <array>
#include <algorithm>
#include <vector>

static prism::CieXY fromProto(luna::proto::UV const & uv)
{
    return {uv.u, uv.v};
}

static prism::RGBColorSpace fromProto(luna::proto::ColorSpace const & cs)
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
        auto colorSpace = fromProto(strand.colorSpace);

        int colorChannels = strand.channels.get();

        auto pixels = std::make_unique<luna::interface::Strand>(
            static_cast<uint32_t>(strand.pixelCount),
            fromProto(strand.begin),
            fromProto(strand.end)
        );

        auto serializer = std::make_unique<StrandSerializerRGB>(
            std::move(pixels),
            colorSpace
        );

        mStrands.emplace_back(std::move(serializer));
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
        mStrands[i]->serialize(builder, str[i]);
        str[i].id = i;
    }

    mDataSocket->write(builder.data(), builder.size());
}

void SecureHost::getStrands(std::vector<luna::interface::Strand *> & strands)
{
    for (auto & strand : mStrands) {
        strands.emplace_back(strand->strand());
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
