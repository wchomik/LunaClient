#include "connectionlegacy.h"

#include <cstdint>
#include <iostream>
#include <limits>

namespace luna {
    const char * ConnectionLegacy::helloMessage = "\x01LunaDaemon";

    ConnectionLegacy::ConnectionLegacy() :
        mIsConnected(false),
        mSocket(0)
    {
        sockInit();
        mSocket = socket(AF_INET, SOCK_DGRAM, 0);
        sockaddr_in address;
        address.sin_family = AF_INET;
        address.sin_port = htons(PORT);
        address.sin_addr.s_addr = htonl (INADDR_ANY);

        if (bind (mSocket, (sockaddr *) &address, sizeof(sockaddr_in))) {
            std::cout << "Could not bind." << std::endl;
            sockClose(mSocket);
            throw std::system_error(errno, std::system_category());
        }
        int val;
        if(setsockopt(mSocket, SOL_SOCKET, SO_BROADCAST,
                      reinterpret_cast<const char *>(&val), sizeof(int))){
            std::cout << "Could not set broadcast." << std::endl;
            sockClose(mSocket);
            throw std::system_error(errno, std::system_category());
        }
    }


    ConnectionLegacy::~ConnectionLegacy(){
        if(mIsConnected){
            mBuffer.reset();
            mBuffer << static_cast<uint8_t>(101);
            mBuffer << static_cast<uint8_t>(2);
            send();
            disconnect();
        }
    }

    bool ConnectionLegacy::isConnected(){
        return mIsConnected;
    }

    bool ConnectionLegacy::connect(){
        sockaddr_in address;
        address.sin_family = AF_INET;
        address.sin_port = htons(PORT);
        address.sin_addr.s_addr = htonl (INADDR_BROADCAST);
        ::sendto(mSocket, helloMessage, strlen(helloMessage), 0,
                 reinterpret_cast<const sockaddr *>(&address), sizeof(sockaddr_in));

        char inbuf[128];
        sockaddr_in fromAddr;
        int fromAddrLen = sizeof(fromAddr);
        int len;
        // TODO handle failure
        while(true){
            len = recvfrom(mSocket, inbuf, 128, 0,  (sockaddr *) &fromAddr, &fromAddrLen);
            inbuf[len] = 0;
            std::cout << inbuf << std::endl;
            if(len != strlen(helloMessage)) break;
        }
        ::connect(mSocket, (sockaddr *) &fromAddr, fromAddrLen);
        std::cout << "Connected to " << std::endl;
        mIsConnected = true;
        return true;
    }

    void ConnectionLegacy::disconnect(){
        mBuffer.reset();
        mBuffer << static_cast<uint8_t>(99);
        send();

        sockaddr_in address = {0};
        address.sin_family = AF_UNSPEC;
        ::connect(mSocket, (sockaddr *) &address, sizeof(sockaddr_in));
        mIsConnected = false;
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

    void ConnectionLegacy::getConfig(Config * config)
    {
        Config::PixelStrandConfig strand;
        strand.count = PIXEL_COUNT;
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

    void ConnectionLegacy::send(){
        ::send(mSocket, mBuffer.data(), mBuffer.count(), 0);
    }
}
