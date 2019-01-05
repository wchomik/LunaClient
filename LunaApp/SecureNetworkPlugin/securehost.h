#pragma once

#include "dtlssocket.h"
#include "StrandSerializer.h"

#include <lunacore/connector.h>

#include <luna/BitDepth.hpp>
#include <luna/proto/Discovery.hpp>

#include <QObject>
#include <QTimer>

struct StrandData {
    std::unique_ptr<lunacore::Strand> strand;
    std::unique_ptr<StrandSerializer> serializer;
};

class SecureHost :
    public QObject,
    public lunacore::Host
{
    Q_OBJECT
public:
    explicit SecureHost(QHostAddress hostAddress, luna::proto::Discovery const * properties);
    ~SecureHost() override;

    QHostAddress address() const noexcept;
    void send();

    std::string displayName() const override;
    void connect() override;
    void disconnect() override;
    bool isConnected() const override;
    void getStrands(std::vector<lunacore::Strand *> &strands) override;
signals:
    void disconnected();

private slots:
    void onConnected(bool value);
    void onResponse(QByteArray const & array);
    void onHeartbeat();
private:
    uint32_t nextAckId();

    QHostAddress mAddress;
    std::unique_ptr<DtlsSocket> mDataSocket;

    std::vector<StrandData> mStrands;
    bool mConnected;

    QTimer mHeartbeat;
    unsigned mHeartbeatsSkipped;
    bool mShouldSendAck;
    uint32_t mCommandId;
};

