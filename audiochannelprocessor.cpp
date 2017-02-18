#include "audiochannelprocessor.h"

#include "fft.h"

namespace luna { namespace audio {
    AudioChannelProcessor::AudioChannelProcessor(const AudioChannelConfig & config) :
        mFFT(config.fft),
        mCount(config.count),
        mIndices(mCount + 1),
        mSums(mCount),
        mFilter(mCount),
        mBaseColors(mCount),
        mLogMul(0.5f / std::log(config.logarithmBase) * config.unitsPerDecade)
    {
        float octaveCount = std::log2(config.fHigh / config.fLow);
        float step = octaveCount / mCount;

        float fMul = config.fLow * mFFT->size() / config.sampleRate;

        int lastIndex = (int) fMul - 1;
        for(int i = 0; i <= mCount; ++i){
            int index = (int)(std::pow(2.0f, step * i) * fMul);
            if(index <= lastIndex) index = lastIndex + 1;
            mIndices[i] = index;
            lastIndex = index;
        }

        for(int i = 0; i < mCount; ++i){
            float f = step * i;
            hsvToRgb(mBaseColors[i], Color(f, 1, 1, 0));
        }
    }

    void AudioChannelProcessor::process(PixelStrand & output, const Eigen::ArrayXf & input)
    {
        for(int i = 0; i < mCount; ++i){
            int i0 = mIndices[i];
            int i1 = mIndices[i + 1];
            mSums[i] = input.segment(i0, i1 - i0).sum();
        }
        mSums = ((mSums + 1e-12f).log());


        float decay = 0.05f;
        // TODO smarter normalization
        mFilter = (mFilter - decay).max(mSums + 4.5f).max(0);
        for(int i = 0; i < mCount; ++i){
            output[i] = mBaseColors[i] * mFilter[i];
        }
    }
}}
