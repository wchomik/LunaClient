#ifndef LUNAAUDIOPROVIDER_H
#define LUNAAUDIOPROVIDER_H

#include <QTimer>

#include "lunaprovider.h"
#include "audiocapture.h"
#include "fft.h"
#include "audiochannelprocessor.h"

namespace luna {
    class LunaAudioProvider : public LunaProvider
    {
    public:
        explicit LunaAudioProvider(QObject * parent = 0);

        void configure(const LunaConfig & config) override;
        ColorMode colorMode(class ColorSpace * outColorSpace) override;

        void start() override;
        void stop() override;

    private slots:
        void onSamplesReady();
    private:
        audio::AudioCapture mAudioCapture;
        audio::FFT mFFT;
        std::vector<audio::AudioChannelProcessor> mProcessors;
    };
}

#endif // LUNAAUDIOPROVIDER_H
