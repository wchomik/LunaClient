#pragma once

#include "AudioCapture.hpp"
#include "FFT.hpp"
#include "AudioChannelProcessor.hpp"
#include "SampleBuffer.hpp"

#include <luna/interface/Provider.hpp>

#include <unordered_map>

class AudioProvider : public luna::interface::Provider
{
public:
    explicit AudioProvider();
    virtual ~AudioProvider();

    void getData(luna::interface::Strand & strands) override;
    void update() override;
private:
    std::unique_ptr<SampleBuffer> mBuffer;
    AudioCapture mAudioCapture;
    FFT mFFT;
    std::unordered_map<const luna::interface::Strand *, std::unique_ptr<AudioChannelProcessor>> mProcessors;

    void createAudioProcessor(luna::interface::Strand const & strand);
};
