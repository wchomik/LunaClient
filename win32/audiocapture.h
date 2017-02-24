#ifndef AUDIOCAPTURE_H
#define AUDIOCAPTURE_H

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
        int sampleRate(){ return mFormat->nSamplesPerSec; }
        int readSamples(luna::SampleBuffer * buffer);
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
