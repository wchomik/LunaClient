#include "audiocapture.h"

#include <stdexcept>

#include "luna/samplebuffer.h"
#include "win32errorhandling.h"

namespace luna { namespace audio {
    AudioCapture::AudioCapture() :
        mFormat(nullptr, &CoTaskMemFree)
    {
        CoInitializeEx(0, COINIT_MULTITHREADED);
    }

    AudioCapture::~AudioCapture()
    {
        CoUninitialize();
    }

    void AudioCapture::configure(int outputChannels)
    {
        HRESULT hr;
        hr = CoCreateInstance(
            __uuidof(MMDeviceEnumerator),
            NULL,
            CLSCTX_ALL,
            __uuidof(IMMDeviceEnumerator),
            (void**)mDevEnum.ReleaseAndGetAddressOf());
        testHR(hr);

        hr = mDevEnum->GetDefaultAudioEndpoint(eRender, eMultimedia,
            mAudioDevice.ReleaseAndGetAddressOf());
        testHR(hr);

        mAudioDevice->Activate(__uuidof(IAudioClient), CLSCTX_ALL, NULL,
            (void**)mAudioClient.ReleaseAndGetAddressOf());
        testHR(hr);

        WAVEFORMATEX * tempFormat;
        hr = mAudioClient->GetMixFormat(&tempFormat);
        mFormat = formatPtr_t(tempFormat, &CoTaskMemFree);
        testHR(hr);

        // TODO add channel mixing
        if(mFormat->nChannels != outputChannels) panic();
        // TODO support non floating point formats
        if(mFormat->wFormatTag != WAVE_FORMAT_IEEE_FLOAT){
            if(mFormat->wFormatTag != WAVE_FORMAT_EXTENSIBLE) panic();
            WAVEFORMATEXTENSIBLE * format = reinterpret_cast<WAVEFORMATEXTENSIBLE *>(mFormat.get());
            if(format->SubFormat != KSDATAFORMAT_SUBTYPE_IEEE_FLOAT) panic();
        }

        REFERENCE_TIME length = static_cast<REFERENCE_TIME>(10000000 * 1.2 / 100);
        mAudioClient->Initialize(
            AUDCLNT_SHAREMODE_SHARED,
            AUDCLNT_STREAMFLAGS_LOOPBACK,
            length,
            0, mFormat.get(), NULL);
        testHR(hr);

        hr = mAudioClient->GetService(__uuidof(IAudioCaptureClient),
            (void**)mAudioCaptureClient.ReleaseAndGetAddressOf());
        testHR(hr);

        hr = mAudioClient->Start();
        testHR(hr);
    }

    int AudioCapture::readSamples(luna::SampleBuffer * buffer)
    {
        int total = 0;
        HRESULT hr;
        uint32_t packetSize;
        hr = mAudioCaptureClient->GetNextPacketSize(&packetSize);
        testHR(hr);
        while (packetSize != 0)
        {
            uint32_t framesAvailable;
            uint8_t * data;
            DWORD flags;
            hr = mAudioCaptureClient->GetBuffer(&data, &framesAvailable, &flags, nullptr, nullptr);

            total += framesAvailable;
            buffer->readFrom(reinterpret_cast<float *>(data), framesAvailable);

            mAudioCaptureClient->ReleaseBuffer(framesAvailable);
            hr = mAudioCaptureClient->GetNextPacketSize(&packetSize);
            testHR(hr);
        }
        return total;
    }


    void AudioCapture::panic(const char * msg)
    {
        throw std::runtime_error(msg);
    }
}}
