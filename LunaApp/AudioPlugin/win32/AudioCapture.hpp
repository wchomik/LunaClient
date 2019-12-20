#pragma once

#include "SampleBuffer.hpp"

#include <wrl.h>
#include <audioclient.h>
#include <mmdeviceapi.h>
#undef interface
#include <cstdint>
#include <memory>

class AudioCapture {
public:
    AudioCapture();
    ~AudioCapture();

    void configure();
	size_t channels() const;
    uint32_t sampleRate() const;
    uint32_t readSamples(SampleBuffer * buffer);
private:
    Microsoft::WRL::ComPtr<IMMDeviceEnumerator> mDevEnum;
    Microsoft::WRL::ComPtr<IMMDevice> mAudioDevice;
    Microsoft::WRL::ComPtr<IAudioClient> mAudioClient;
    Microsoft::WRL::ComPtr<IAudioCaptureClient> mAudioCaptureClient;
    struct CoTaskMemDeleter {
        void operator()(WAVEFORMATEX * p) const {
            CoTaskMemFree(p);
        }
    };
    typedef std::unique_ptr<WAVEFORMATEX, CoTaskMemDeleter> formatPtr_t;
    formatPtr_t mFormat;
};
