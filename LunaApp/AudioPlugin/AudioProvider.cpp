#include "AudioProvider.hpp"

#include <luna/interface/Strand.hpp>

AudioProvider::AudioProvider() :
    mFFT(1 << 13, FFT::magnitude)
{
    const uint32_t channelCount = 2;
    mAudioCapture.configure();
	mBuffer = std::make_unique<SampleBuffer>(1 << 13, mAudioCapture.channels());
}

AudioProvider::~AudioProvider() = default;

void AudioProvider::getData(luna::interface::Strand & strand)
{
    auto & fftIn = mFFT.input();
    
    uint32_t const side = (strand.beginPosition()[0] > 0) ? 1 : 0;
    
    auto channel = mBuffer->channel(side);
    
    for (uint32_t i = 0; i < mFFT.size(); ++i){
        fftIn[i] = channel[i];
    }
    
    mFFT.compute();

    auto it = mProcessors.find(&strand);
    if (mProcessors.end() == it) {
        createAudioProcessor(strand);
    }

    AudioChannelProcessor * processor = mProcessors[&strand].get();

    processor->process(strand, mFFT.magnitudes());
}

void AudioProvider::update()
{
    uint32_t count = mAudioCapture.readSamples(mBuffer.get());
}

void AudioProvider::createAudioProcessor(luna::interface::Strand const & strand)
{
    AudioChannelConfig audioConf;
    audioConf.fftResolution = mFFT.size();
    audioConf.fLow = 100;
    audioConf.fHigh = 16000;
    audioConf.sampleRate = mAudioCapture.sampleRate();
    audioConf.unitsPerDecade = 4.0f;
    audioConf.count = strand.size();
    mProcessors[&strand] = std::make_unique<AudioChannelProcessor>(audioConf);
}
