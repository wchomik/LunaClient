#ifndef AUDIOCHANNELPROCESSOR_H
#define AUDIOCHANNELPROCESSOR_H

#include <vector>
#include <Eigen/Core>

#include "colorutils.h"

namespace luna { namespace audio {
    struct AudioChannelConfig{
        class FFT * fft = nullptr;
        int count = 0;
        float fLow = 1;
        float fHigh = 1;
        int sampleRate = 48000;
        float logarithmBase = 10;
        float unitsPerDecade = 2;
    };

    class AudioChannelProcessor
    {
    public:
        explicit AudioChannelProcessor(const AudioChannelConfig & config);
        void process(PixelStrand & output, const Eigen::ArrayXf & input);
    private:
        class FFT * const mFFT;
        const int mCount;
        std::vector<int> mIndices;
        Eigen::ArrayXf mSums;
        Eigen::ArrayXf mFilter;
        PixelStrand mBaseColors;
        const float mLogMul;
    };
}}

#endif // AUDIOCHANNELPROCESSOR_H
