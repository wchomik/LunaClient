#pragma once
#include "sslsink.hpp"

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

class ControlSocket : public QObject
{
    Q_OBJECT
public:
    explicit ControlSocket(QHostAddress address, uint16_t port, luna::client::Listener * listener);
    QHostAddress peerAddress() const;
    luna::client::Encoder & encoder();

signals:
    void disconnected();

private slots:
    void handleSslErrors(QList<QSslError> const & errors);
    void handleTcpConnected();
    void handleSslConnected();
    void readSocket();

private:
    QSslCertificate mLocalCertificate;
    QSslCertificate mCaCertificate;
    QSslKey mPrivateKey;
    QSslConfiguration mConfiguration;
    QSslSocket mSocket;

    SslSink mSslSink;
    luna::client::Encoder mEncoder;
    luna::client::Decoder mDecoder;
    luna::Defragmenter mDefragmenter;
};
