#include "audioprovider.h"

#include "config.h"

namespace luna {
    using namespace audio;

    AudioProvider::AudioProvider(QObject * parent) :
        Provider(parent),
        mAudioCapture(this),
        mFFT(1 << 13, FFT::magnitude)
    {
        QObject::connect(&mAudioCapture, &audio::AudioCapture::samplesReady,
                         this, &AudioProvider::onSamplesReady);
    }

    void AudioProvider::configure(const Config &config)
    {
        Provider::configure(config);
        mAudioCapture.configure(config.pixelStrands.size(), 100.0);

        audio::AudioChannelConfig audioConf;
        audioConf.fft = &mFFT;
        audioConf.fLow = 100;
        audioConf.fHigh = 16000;
        audioConf.sampleRate = mAudioCapture.sampleRate();
        audioConf.unitsPerDecade = 8.0f;
        mProcessors.clear();
        for(int i = 0; i < config.pixelStrands.size(); ++i){
            audioConf.count = config.pixelStrands[i].count;
            mProcessors.emplace_back(audioConf);
        }
    }

    ColorMode AudioProvider::colorMode(class ColorSpace * outColorSpace)
    {
        return ColorMode::fullWhiteBalanced;
    }

    void AudioProvider::start()
    {
        mAudioCapture.start();
    }

    void AudioProvider::stop()
    {
        mAudioCapture.stop();
    }

    void AudioProvider::onSamplesReady()
    {
        auto & fftIn = mFFT.input();
        for(int i = 0; i < 2; ++i){
            auto channel = mAudioCapture.sampleBuffer()->channel(i);
            for(int j = 0; j < mFFT.size(); ++j){
                fftIn[j] = channel[j];
            }
            mFFT.compute();
            auto & processor = mProcessors[i];
            auto & strand = mPixelStrands[i];
            processor.process(strand, mFFT.magnitudes());
        }

        emit dataReady();
    }
}
