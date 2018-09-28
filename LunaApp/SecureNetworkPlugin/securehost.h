#pragma once

#include "sslsink.hpp"
#include "dtlssocket.h"

#include <lunacore/connector.h>

#include <luna/BitDepth.hpp>
#include <luna/client/Decoder.hpp>
#include <luna/client/Encoder.hpp>
#include <luna/client/Listener.hpp>
#include <luna/Defragmenter.hpp>

#include <QObject>
#include <QHostAddress>
#include <QSslSocket>
#include <QSslConfiguration>
#include <QSslCertificate>
#include <QSslKey>


struct StrandData {
    std::unique_ptr<luna::Strand> strand;
    luna::BitDepth bitDepth;
};

class SecureHost :
    public QObject,
    public luna::Host,
    private luna::client::Listener
{
    Q_OBJECT
public:
    explicit SecureHost(QHostAddress hostAddress);
    ~SecureHost() override;

    void send();
signals:
    void disconnected();
private:
    QSslCertificate mLocalCertificate;
    QSslCertificate mCaCertificate;
    QSslKey mPrivateKey;
    QSslConfiguration mConfiguration;
    QSslSocket mCommandSocket;

    SslSink mSslSink;
    luna::client::Encoder mEncoder;
    luna::client::Decoder mDecoder;
    luna::Defragmenter mDefragmenter;
    std::unique_ptr<DtlsSocket> mDataSocket;

    std::vector<StrandData> mStrands;
    bool mConnected;
    // Host interface
public:
    std::string displayName() const override;
    void connect() override;
    void disconnect() override;
    bool isConnected() const override;
    void getStrands(std::vector<luna::Strand *> &strands) override;

    // Listener interface
private:
    void strandConfigurationReceived(const luna::LunaConfiguration &configuration) override;
    void dataChannelOpened(const luna::DataChannelConfiguration &configuration) override;
};

