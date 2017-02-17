#include "lunaprovider.h"

#include "lunaconfig.h"

namespace luna {
    LunaProvider::LunaProvider(QObject * parent) :
        QObject(parent)
    {}

    LunaProvider::~LunaProvider()
    {}

    void LunaProvider::configure(const LunaConfig &config)
    {
        mPixelStrands.clear();
        mWhiteStrands.clear();
        for(auto & strand : config.pixelStrands){
            mPixelStrands.emplace_back(strand.count);
            for(Color & pixel : mPixelStrands.back()){
                pixel = Color::Zero();
            }
        }
        for(auto strand : config.whiteStrands){
            mWhiteStrands.emplace_back(0);
        }
    }
}
