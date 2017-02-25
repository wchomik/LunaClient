#include "connectionlegacy.h"

#include <cstdint>
#include <iostream>
#include <limits>

namespace luna {
    static int constexpr cstrlen(const char * str)
    {
        return *str ? 1 + cstrlen(str + 1) : 0;
    }


    static constexpr char helloMessage[] = "\x01LunaDaemon";
    static constexpr int helloLen = cstrlen(helloMessage);

    ConnectionLegacy::ConnectionLegacy() :
        mIsConnected(false)
    {
        mHostList.emplace_back(std::make_shared<Host>("Default"));

        mSocket.setBroadcast(true);
        mSocket.setNonBlock(true);
        net::Address any(net::Address::ANY, PORT);
        mSocket.bind(any);
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

    void ConnectionLegacy::update()
    {
        if(!mIsConnected){
            net::Address broadcast(net::Address::BROADCAST, PORT);
            mSocket.sendTo(helloMessage, helloLen, broadcast);
        }
        bool shouldConnect = false;
        net::Address from;
        for(;;){
            char inbuf[128];
            int len = mSocket.receiveFrom(inbuf, sizeof(inbuf), from);
            if(len < 0) break;

            inbuf[len] = 0;
            // TODO add some sort of validation
            if(helloLen != len) {
                mIsConnected = true;
                shouldConnect = true;
                break;
            }
        }
        if(shouldConnect){
            mSocket.connect(from);
        }
    }

    void ConnectionLegacy::connect(const Host * host){
        if(host != nullptr){

        }
    }

    void ConnectionLegacy::disconnect(){
        mBuffer.reset();
        mBuffer << static_cast<uint8_t>(99);
        send();

        mSocket.disconnect();
        mIsConnected = false;
    }

    void ConnectionLegacy::sendPixels(const std::vector<PixelStrand> & pixelStrands,
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

    const std::vector<std::shared_ptr<Host> > &ConnectionLegacy::getHosts()
    {
        return mHostList;
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

        config->colorSpace = ColorSpace::ws2812();
    }

    void ConnectionLegacy::send(){
        mSocket.send(mBuffer.data(), mBuffer.count());
    }
}
