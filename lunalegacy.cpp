#include "lunalegacy.h"

#include <iostream>

#include <QThread>


namespace luna {
    const char * LunaLegacy::helloMessage = "\x01LunaDaemon";

    LunaLegacy::LunaLegacy(QObject * parent) :
        Luna(parent),
        mIsConnected(false),
        mSocket(this)
    {
        QObject::connect(&mSocket, &QUdpSocket::readyRead,
                         this, &LunaLegacy::datagramReceived);
        makeConfig();
    }

    LunaLegacy::~LunaLegacy(){

    }

    bool LunaLegacy::isConnected(){
        return mIsConnected;
    }

    void LunaLegacy::connect(){
        mSocket.bind(port);
        mSocket.writeDatagram(helloMessage, strlen(helloMessage), QHostAddress::Broadcast, port);
        mSocket.connectToHost(QHostAddress::Any, port);
    }

    void LunaLegacy::disconnect(){
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
            for(const Color & pixel : strand){
                Eigen::Matrix<uint8_t, 4, 1> rgb =
                    pixel.cwiseProduct(multiplier).cast<uint8_t>();
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
    }

    void LunaLegacy::datagramReceived(){
        quint64 size = mSocket.pendingDatagramSize();
        std::cout << "Got something " << size << std::endl;
        std::vector<char> data(size + 1);
        QHostAddress senderIp;

        quint16 senderPort;
        mSocket.readDatagram(data.data(), data.size(), &senderIp, &senderPort);
        if(strcmp(data.data(), helloMessage) != 0){
            qDebug() << senderIp.toString();
            mSocket.disconnectFromHost();
            mSocket.connectToHost(senderIp, port);
            mIsConnected = true;
            emit connected();
        }
    }

    void LunaLegacy::send(){
        mSocket.write(mBuffer.data(), mBuffer.count());
    }

    void LunaLegacy::makeConfig()
    {
        LunaConfig::PixelStrandConfig strand;
        strand.count = 120;
        strand.direction = LunaConfig::bottomToTop;

        strand.position = LunaConfig::left;
        mConfig.pixelStrands.push_back(strand);
        strand.position = LunaConfig::right;
        mConfig.pixelStrands.push_back(strand);

        mConfig.whiteStrands.push_back(LunaConfig::left);
        mConfig.whiteStrands.push_back(LunaConfig::right);
    }
}
