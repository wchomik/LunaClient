#pragma once

#include "dtlssocket.h"
#include "controlsocket.h"
#include "StrandSerializer.h"

#include <lunacore/connector.h>

#include <luna/BitDepth.hpp>
#include <luna/client/Listener.hpp>

#include <QObject>

struct StrandData {
    std::unique_ptr<lunacore::Strand> strand;
    std::unique_ptr<StrandSerializer> serializer;
};

class SecureHost :
    public QObject,
    public lunacore::Host,
    private luna::client::Listener
{
    Q_OBJECT
public:
    explicit SecureHost(QHostAddress hostAddress);
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

private:
    QHostAddress mAddress;
    std::unique_ptr<ControlSocket> mControlSocket;
    std::unique_ptr<DtlsSocket> mDataSocket;

    std::vector<StrandData> mStrands;
    bool mConnected;

private:
    void strandConfigurationReceived(const luna::LunaConfiguration &configuration) override;
    void dataChannelOpened(const luna::DataChannelConfiguration &configuration) override;
};

