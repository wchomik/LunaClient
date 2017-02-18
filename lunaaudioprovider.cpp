#include "lunaaudioprovider.h"

#include "lunaconfig.h"

namespace luna {
    using namespace audio;

    LunaAudioProvider::LunaAudioProvider(QObject * parent) :
        LunaProvider(parent),
        mAudioCapture(this),
        mFFT(1 << 13, FFT::magnitude)
    {
        QObject::connect(&mAudioCapture, &audio::AudioCapture::samplesReady,
                         this, &LunaAudioProvider::onSamplesReady);
    }

    void LunaAudioProvider::configure(const LunaConfig &config)
    {
        LunaProvider::configure(config);
        mAudioCapture.configure(config.pixelStrands.size(), 100.0);

        audio::AudioChannelConfig audioConf;
        audioConf.fft = &mFFT;
        audioConf.fLow = 100;
        audioConf.fHigh = 16000;
        audioConf.sampleRate = mAudioCapture.sampleRate();
        audioConf.unitsPerDecade = 0.5f;
        mProcessors.clear();
        for(int i = 0; i < config.pixelStrands.size(); ++i){
            audioConf.count = config.pixelStrands[i].count;
            mProcessors.emplace_back(audioConf);
        }
    }

    ColorMode LunaAudioProvider::colorMode()
    {
        return ColorMode::nativeWhiteBalancedGamma;
    }

    void LunaAudioProvider::start()
    {
        mAudioCapture.start();
    }

    void LunaAudioProvider::stop()
    {
        mAudioCapture.stop();
    }

    void LunaAudioProvider::onSamplesReady()
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
