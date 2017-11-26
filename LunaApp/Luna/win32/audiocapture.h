#ifndef AUDIOCAPTURE_H
#define AUDIOCAPTURE_H

#include <cstdint>
#include <memory>

#include <wrl.h>
#include <Audioclient.h>
#include <mmdeviceapi.h>

#include "luna/samplebuffer.h"

namespace luna { namespace audio {
    class AudioCapture {
    public:
        AudioCapture();
        ~AudioCapture();

        void configure(int outputChannels);
        uint32_t sampleRate(){ return mFormat->nSamplesPerSec; }
        uint32_t readSamples(luna::SampleBuffer * buffer);
    private:
        void panic(const char *msg = "");

        Microsoft::WRL::ComPtr<IMMDeviceEnumerator> mDevEnum;
        Microsoft::WRL::ComPtr<IMMDevice> mAudioDevice;
        Microsoft::WRL::ComPtr<IAudioClient> mAudioClient;
        Microsoft::WRL::ComPtr<IAudioCaptureClient> mAudioCaptureClient;
        typedef std::unique_ptr<WAVEFORMATEX, decltype(&CoTaskMemFree)> formatPtr_t;
        formatPtr_t mFormat;
    };
}}

#endif // AUDIOCAPTURE_H
