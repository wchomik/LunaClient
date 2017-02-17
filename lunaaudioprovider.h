#ifndef LUNAAUDIOPROVIDER_H
#define LUNAAUDIOPROVIDER_H

#include <QTimer>

#include "lunaprovider.h"
#include "audiocapture.h"

namespace luna {
    class LunaAudioProvider : public LunaProvider
    {
    public:
        explicit LunaAudioProvider(QObject * parent = 0);

        void configure(const LunaConfig &config) override;
        ColorMode colorMode() override;

        void start() override;
        void stop() override;

    private:
        audio::AudioCapture mAudioCapture;
    };
}

#endif // LUNAAUDIOPROVIDER_H
