#ifndef LUNAAUDIOPROVIDER_H
#define LUNAAUDIOPROVIDER_H

#include "provider.h"
#include "audiocapture.h"
#include "fft.h"
#include "audiochannelprocessor.h"
#include "samplebuffer.h"

namespace luna {
    class AudioProvider : public Provider
    {
    public:
        AudioProvider();
        void configure(const Config & config) override;
        ColorMode colorMode(class ColorSpace * outColorSpace) override;
        bool getData(std::vector<PixelStrand> & pixelStrands, std::vector<ColorScalar> & whiteStrands) override;
    private:
        std::unique_ptr<SampleBuffer> mBuffer;
        audio::AudioCapture mAudioCapture;
        audio::FFT mFFT;
        std::vector<audio::AudioChannelProcessor> mProcessors;
    };
}

#endif // LUNAAUDIOPROVIDER_H
