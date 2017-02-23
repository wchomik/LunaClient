#include "provider.h"

#include "config.h"

namespace luna {
    Provider::Provider(QObject * parent) :
        QObject(parent)
    {}

    Provider::~Provider()
    {}

    void Provider::configure(const Config &config)
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
