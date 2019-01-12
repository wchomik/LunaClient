#include "AudioChannelProcessor.hpp"

#include "FFT.hpp"

AudioChannelProcessor::AudioChannelProcessor(const AudioChannelConfig & config) :
    mCount(config.count),
    mFFTResolution(config.fftResolution),
    mIndices(mCount + 1),
    mSums(mCount),
    mFilter(mCount),
    mBaseColors(mCount),
    mLogMul(0.5f / std::log(config.logarithmBase) * config.unitsPerDecade),
    mFilteredNorm(0)
{
    float octaveCount = std::log2(config.fHigh / config.fLow);
    float step = octaveCount / mCount;

    float fMul = config.fLow * mFFTResolution / config.sampleRate;

    int lastIndex = static_cast<int>(fMul) - 1;
    for(size_t i = 0; i <= mCount; ++i){
        int index = static_cast<int>(std::pow(2.0f, step * i) * fMul);
        if(index <= lastIndex) index = lastIndex + 1;
        mIndices[i] = index;
        lastIndex = index;
    }

    for(size_t i = 0; i < mCount; ++i){
        float f = step * i;
        prism::HSV hsv;
        hsv << f, 1, 1, 0;
        mBaseColors[i] = prism::rec2020().transform(prism::toRgb(hsv));
    }

    mFilter.setZero();
}

void AudioChannelProcessor::process(luna::interface::Strand & output, const Eigen::ArrayXf & input) {
    constexpr float maxRise = 2.0f;
    constexpr float smoothingFactor = 0.99f;
    constexpr float decayRate = 0.05f;
    constexpr float offset = 1.0f;

    for(size_t i = 0; i < mCount; ++i){
        auto i0 = mIndices[i];
        auto i1 = mIndices[i + 1];
        mSums[i] = input.segment(i0, i1 - i0).sum();
    }
    float norm = std::log(mSums.maxCoeff() + 1e-12f);
    if(norm > mFilteredNorm + maxRise){
        mFilteredNorm = norm - maxRise;
    }
    mFilteredNorm = mFilteredNorm * smoothingFactor + norm * (1 - smoothingFactor);

    mSums = (((mSums + 1e-12f).log() - mFilteredNorm) * mLogMul + offset);

    mFilter = (mFilter - decayRate).max(mSums).max(0);
    for(size_t i = 0; i < mCount; ++i){
        prism::CieXYZ color;
        static_cast<prism::Coefficients &>(color) = mBaseColors[i] * mFilter[i];
        output[i].color(color);
    }
}
