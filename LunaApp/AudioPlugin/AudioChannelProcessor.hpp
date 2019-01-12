#pragma once

#include <prism/Prism.hpp>
#include <luna/interface/Strand.hpp>

#include <Eigen/Dense>

#include <cstdint>
#include <vector>

struct AudioChannelConfig {
    uint32_t count = 0;
    uint32_t fftResolution = 0;
    float fLow = 1;
    float fHigh = 1;
    uint32_t sampleRate = 48000;
    float logarithmBase = 10;
    float unitsPerDecade = 2;
};

class AudioChannelProcessor {
public:
    explicit AudioChannelProcessor(const AudioChannelConfig & config);
    void process(luna::interface::Strand & output, const Eigen::ArrayXf & input);
private:
    const uint32_t mCount;
    const uint32_t mFFTResolution;
    std::vector<uint32_t> mIndices;
    Eigen::ArrayXf mSums;
    Eigen::ArrayXf mFilter;
    std::vector<prism::CieXYZ> mBaseColors;
    const float mLogMul;
    float mFilteredNorm;
};
