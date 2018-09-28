#pragma once

#include <luna/StreamSink.hpp>

#include <QSslSocket>

class SslSink : public luna::StreamSink
{
public:
    SslSink(QSslSocket * ssl) : mSsl(ssl) {}

    void receiveStream(const uint8_t *data, size_t size) override;
private:
    QSslSocket * mSsl;

};

inline void SslSink::receiveStream(uint8_t const * data, size_t size)
{
    mSsl->write(reinterpret_cast<char const *>(data), static_cast<qint64>(size));
}
