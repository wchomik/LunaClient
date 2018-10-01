#ifndef AUDIOCHANNELPROCESSOR_H
#define AUDIOCHANNELPROCESSOR_H

#include <cstdint>
#include <vector>
#include <Eigen/Core>

#include <lunacore/colorutils.h>

struct AudioChannelConfig {
    class FFT * fft = nullptr;
    uint32_t count = 0;
    float fLow = 1;
    float fHigh = 1;
    uint32_t sampleRate = 48000;
    float logarithmBase = 10;
    float unitsPerDecade = 2;
};

class AudioChannelProcessor {
public:
    explicit AudioChannelProcessor(const AudioChannelConfig & config);
    void process(lunacore::Color * output, const Eigen::ArrayXf & input);
private:
    class FFT * mFFT;
    const uint32_t mCount;
    std::vector<uint32_t> mIndices;
    Eigen::ArrayXf mSums;
    Eigen::ArrayXf mFilter;
    lunacore::ColorVector mBaseColors;
    const float mLogMul;
    float mFilteredNorm;
};

#endif // AUDIOCHANNELPROCESSOR_H
