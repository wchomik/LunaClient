#include "connectionlegacy.h"

#include <QThread>


namespace luna {
    const char * ConnectionLegacy::helloMessage = "\x01LunaDaemon";

    ConnectionLegacy::ConnectionLegacy(QObject * parent) :
        Connection(parent),
        mIsConnected(false),
        mSocket(this),
        mKeepAliveTimer(this)
    {
        QObject::connect(&mSocket, &QUdpSocket::readyRead,
                         this, &ConnectionLegacy::datagramReceived);
        QObject::connect(&mKeepAliveTimer, &QTimer::timeout,
                         this, &ConnectionLegacy::keepAliveTimeout);

        mKeepAliveTimer.setInterval(1000);
        mSocket.bind(port);
    }

    ConnectionLegacy::~ConnectionLegacy(){

    }

    bool ConnectionLegacy::isConnected(){
        return mIsConnected;
    }

    void ConnectionLegacy::connect(){
        mSocket.writeDatagram(helloMessage, strlen(helloMessage), QHostAddress::Broadcast, port);
    }

    void ConnectionLegacy::disconnect(){
        mKeepAliveTimer.stop();
        mBuffer.reset();
        mBuffer << static_cast<uint8_t>(99);
        send();
        mSocket.disconnectFromHost();
        mIsConnected = false;
        disconnected();
    }

    void ConnectionLegacy::update(const std::vector<PixelStrand> & pixelStrands,
                            const std::vector<ColorScalar> & whiteStrands){
        mBuffer.reset();
        mBuffer << static_cast<uint8_t>(101);
        mBuffer << static_cast<uint8_t>(61);
        for(ColorScalar brightness : whiteStrands){
            brightness = std::max<ColorScalar>(0.0, std::min<ColorScalar>(1.0, brightness));
            uint16_t value = static_cast<uint16_t>(std::numeric_limits<uint16_t>::max() * brightness);
            mBuffer << value;
        }
        for(const PixelStrand & strand : pixelStrands){
            Color error = Color::Zero();
            Color corrected;
            Color clampedRounded;
            for(const Color & pixel : strand){
                corrected = pixel * 255 + error;
                clampedRounded = corrected.array().max(0).min(255).round().matrix();
                error = corrected - clampedRounded;
                Eigen::Matrix<uint8_t, 4, 1> rgb = clampedRounded.cast<uint8_t>();
                mBuffer.write(rgb.data(), 3);
            }
        }
        send();
    }

    void ConnectionLegacy::shutdown(){
        mBuffer.reset();
        mBuffer << static_cast<uint8_t>(101);
        mBuffer << static_cast<uint8_t>(2);
        send();
        disconnect();
    }

    void ConnectionLegacy::getConfig(Config * config)
    {
        Config::PixelStrandConfig strand;
        strand.count = pixelCount;
        strand.direction = Config::bottomToTop;

        config->pixelStrands.clear();
        config->whiteStrands.clear();

        strand.position = Config::left;
        config->pixelStrands.push_back(strand);
        strand.position = Config::right;
        config->pixelStrands.push_back(strand);

        config->whiteStrands.push_back(Config::left);
        config->whiteStrands.push_back(Config::right);
    }

    void ConnectionLegacy::datagramReceived(){
        quint64 size = mSocket.pendingDatagramSize();
        std::vector<char> data(size + 1);
        QHostAddress senderIp;

        quint16 senderPort;
        mSocket.readDatagram(data.data(), data.size(), &senderIp, &senderPort);
        if(strcmp(data.data(), helloMessage) != 0){
            mSocket.connectToHost(senderIp, senderPort);
            mIsConnected = true;
            mKeepAliveTimer.start();
            connected();
        }
    }

    void ConnectionLegacy::keepAliveTimeout()
    {
        mBuffer.reset();
        send();
    }

    void ConnectionLegacy::send(){
        mSocket.write(mBuffer.data(), mBuffer.count());
    }
}
