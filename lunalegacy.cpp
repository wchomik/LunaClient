#include "lunalegacy.h"

#include <QThread>


namespace luna {
    const char * LunaLegacy::helloMessage = "\x01LunaDaemon";

    LunaLegacy::LunaLegacy(QObject * parent) :
        Luna(parent),
        mIsConnected(false),
        mSocket(this),
        mKeepAliveTimer(this)
    {
        QObject::connect(&mSocket, &QUdpSocket::readyRead,
                         this, &LunaLegacy::datagramReceived);
        QObject::connect(&mKeepAliveTimer, &QTimer::timeout,
                         this, &LunaLegacy::keepAliveTimeout);

        mKeepAliveTimer.setInterval(1000);
        makeConfig();
        mSocket.bind(port);
    }

    LunaLegacy::~LunaLegacy(){

    }

    bool LunaLegacy::isConnected(){
        return mIsConnected;
    }

    QAbstractListModel * LunaLegacy::devices(){
        return nullptr;
    }


    void LunaLegacy::connect(){
        mSocket.writeDatagram(helloMessage, strlen(helloMessage), QHostAddress::Broadcast, port);
    }

    void LunaLegacy::disconnect(){
        mKeepAliveTimer.stop();
        mBuffer.reset();
        mBuffer << static_cast<uint8_t>(99);
        send();
        mSocket.disconnectFromHost();
        mIsConnected = false;
        emit disconnected();
    }

    void LunaLegacy::update(const std::vector<PixelStrand> & pixelStrands,
                            const std::vector<ColorScalar> & whiteStrands){
        mBuffer.reset();
        mBuffer << static_cast<uint8_t>(101);
        mBuffer << static_cast<uint8_t>(61);
        for(ColorScalar brightness : whiteStrands){
            uint16_t value = static_cast<uint16_t>(std::numeric_limits<uint16_t>::max() * brightness);
            mBuffer << value;
        }
        Color multiplier = Color::Constant(255);
        for(const PixelStrand & strand : pixelStrands){
            Color error = Color::Zero();
            Color corrected;
            Color clampedRounded;
            for(const Color & pixel : strand){
                corrected = pixel.cwiseProduct(multiplier) + error;
                clampedRounded = corrected.array().max(0).min(255).round().matrix();
                error = corrected - clampedRounded;
                Eigen::Matrix<uint8_t, 4, 1> rgb = clampedRounded.cast<uint8_t>();
                mBuffer.write(rgb.data(), 3);
            }
        }
        send();
    }

    void LunaLegacy::shutdown(){
        mBuffer.reset();
        mBuffer << static_cast<uint8_t>(101);
        mBuffer << static_cast<uint8_t>(2);
        send();
        disconnect();
    }

    void LunaLegacy::discover()
    {

    }

    void LunaLegacy::datagramReceived(){
        quint64 size = mSocket.pendingDatagramSize();
        std::vector<char> data(size + 1);
        QHostAddress senderIp;

        quint16 senderPort;
        mSocket.readDatagram(data.data(), data.size(), &senderIp, &senderPort);
        if(strcmp(data.data(), helloMessage) != 0){
            qDebug() << senderIp.toString();
            mSocket.connectToHost(senderIp, senderPort);
            mIsConnected = true;
            mKeepAliveTimer.start();
            emit connected();
        }
    }

    void LunaLegacy::keepAliveTimeout()
    {
        mBuffer.reset();
        send();
    }

    void LunaLegacy::send(){
        mSocket.write(mBuffer.data(), mBuffer.count());
    }

    void LunaLegacy::makeConfig()
    {
        LunaConfig::PixelStrandConfig strand;
        strand.count = pixelCount;
        strand.direction = LunaConfig::bottomToTop;

        strand.position = LunaConfig::left;
        mConfig.pixelStrands.push_back(strand);
        strand.position = LunaConfig::right;
        mConfig.pixelStrands.push_back(strand);

        mConfig.whiteStrands.push_back(LunaConfig::left);
        mConfig.whiteStrands.push_back(LunaConfig::right);
    }
}
