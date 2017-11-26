#ifndef LUNAAUDIOPROVIDER_H
#define LUNAAUDIOPROVIDER_H

#include <unordered_map>
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
        void getData(std::vector<Strand *> &strands) override;
    private:
        std::unique_ptr<SampleBuffer> mBuffer;
        audio::AudioCapture mAudioCapture;
        audio::FFT mFFT;
        std::unordered_map<const Strand *, std::unique_ptr<audio::AudioChannelProcessor>> mProcessors;

        void createAudioProcessor(const Strand * strand);
    };
}

#endif // LUNAAUDIOPROVIDER_H
