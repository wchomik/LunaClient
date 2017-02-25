#include "illuminationprovider.h"

#include "config.h"

namespace luna {
    IlluminationProvider::IlluminationProvider() :
        mColor(1, 1, 1, 1),
        mWhiteness(0.0)
    {}

    void IlluminationProvider::configure(const Config &){}


    ColorMode IlluminationProvider::colorMode(class ColorSpace *)
    {
        return ColorMode::fullWhiteBalanced;
    }

    bool IlluminationProvider::getData(std::vector<PixelStrand> &pixelStrands, std::vector<ColorScalar> &whiteStrands)
    {
        if(mNewData){
            for(PixelStrand & strand : pixelStrands){
                for(Color & pixel : strand){
                    pixel = mColor;
                }
            }
            for(ColorScalar & strand : whiteStrands){
                strand = mWhiteness;
            }
            mNewData = false;
            return true;
        }else{
            return false;
        }
    }
}
