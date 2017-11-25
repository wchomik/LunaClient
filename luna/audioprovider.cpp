#include "audioprovider.h"

#include "strand.h"
#include "config.h"

namespace luna {
    using namespace audio;

    void AudioProvider::getData(std::vector<Strand *> & strands) {
        uint32_t count = mAudioCapture.readSamples(mBuffer.get());

        if(0 == count) return;

        auto & fftIn = mFFT.input();
        for (auto strand : strands) {
            uint32_t side = (strand->config().begin[0] > 0) ? 1 : 0;
            auto channel = mBuffer->channel(side);
            for (uint32_t i = 0; i < mFFT.size(); ++i){
                fftIn[i] = channel[i];
            }
            mFFT.compute();

            auto it = mProcessors.find(strand);
            if (mProcessors.end() == it) {
                createAudioProcessor(strand);
            }
            AudioChannelProcessor * processor = mProcessors[strand].get();


            processor->process(strand->pixels(), mFFT.magnitudes());
        }
    }

    void AudioProvider::createAudioProcessor(const Strand * strand) {
        AudioChannelConfig audioConf;
        audioConf.fft = &mFFT;
        audioConf.fLow = 100;
        audioConf.fHigh = 16000;
        audioConf.sampleRate = mAudioCapture.sampleRate();
        audioConf.unitsPerDecade = 4.0f;
        audioConf.count = strand->config().count;
        mProcessors[strand] = std::make_unique<AudioChannelProcessor>(audioConf);
    }

    AudioProvider::AudioProvider() :
        mFFT(1 << 13, FFT::magnitude)
    {
        const uint32_t channelCount = 2;
        mBuffer = std::make_unique<SampleBuffer>(1 << 13, channelCount);
        mAudioCapture.configure(channelCount);
    }

    /*void AudioProvider::configure(const Config &config)
    {
        const int channelCount = config.pixelStrands.size();
        mBuffer = std::make_unique<SampleBuffer>(1 << 13, channelCount);
        mAudioCapture.configure(channelCount);

        audio::AudioChannelConfig audioConf;
        audioConf.fft = &mFFT;
        audioConf.fLow = 100;
        audioConf.fHigh = 16000;
        audioConf.sampleRate = mAudioCapture.sampleRate();
        audioConf.unitsPerDecade = 4.0f;
        mProcessors.clear();
        for(int i = 0; i < channelCount; ++i){
            audioConf.count = config.pixelStrands[i].count;
            mProcessors.emplace_back(audioConf);
        }
    }

    ColorMode AudioProvider::colorMode(class ColorSpace *)
    {
        return ColorMode::fullWhiteBalanced;
    }

    bool AudioProvider::getData(std::vector<PixelStrand> &pixelStrands, std::vector<ColorScalar> &whiteStrands)
    {
        int count = mAudioCapture.readSamples(mBuffer.get());
        if(count == 0){
            return false;
        }
        auto & fftIn = mFFT.input();
        for(int i = 0; i < mProcessors.size(); ++i){
            auto channel = mBuffer->channel(i);
            for(int j = 0; j < mFFT.size(); ++j){
                fftIn[j] = channel[j];
            }
            mFFT.compute();
            auto & processor = mProcessors[i];
            auto & strand = pixelStrands[i];
            processor.process(strand, mFFT.magnitudes());
        }
        for(auto & white : whiteStrands){
            white = 0;
        }
        return true;
    }*/
}
