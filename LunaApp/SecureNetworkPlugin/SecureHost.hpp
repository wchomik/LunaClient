#pragma once

#include "DTLSSocket.hpp"
#include "StrandSerializer.hpp"

#include <luna/interface/Connector.hpp>
#include <luna/proto/Discovery.hpp>

#include <QObject>
#include <QTimer>

class SecureHost : public QObject
{
    Q_OBJECT
public:
    explicit SecureHost(QHostAddress hostAddress, luna::proto::Discovery const * properties);
    ~SecureHost() override;

    QHostAddress address() const noexcept;
    void send();

    void getStrands(std::vector<luna::interface::Strand *> & strands);
    bool connected() const { return mConnected; }
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

    std::vector<std::unique_ptr<StrandSerializer>> mStrands;
    bool mConnected;

    QTimer mHeartbeat;
    unsigned mHeartbeatsSkipped;
    bool mShouldSendAck;
    uint32_t mCommandId;
};
