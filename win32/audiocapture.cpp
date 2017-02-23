
#include "audiocapture.h"

#include <QDebug>
#include "luna/samplebuffer.h"
#include "win32errorhandling.h"

namespace luna { namespace audio {
    AudioCapture::AudioCapture(QObject * parent) :
        QObject(parent),
        mTimer(this),
        mFormat(nullptr, &CoTaskMemFree)
    {
        QObject::connect(&mTimer, &QTimer::timeout, this, &AudioCapture::readSamples);
        CoInitializeEx(0, COINIT_MULTITHREADED);
    }

    AudioCapture::~AudioCapture()
    {
        CoUninitialize();
    }

    void AudioCapture::configure(int outputChannels, float updateRate)
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

        REFERENCE_TIME length = static_cast<REFERENCE_TIME>(10000000 * 1.2f / updateRate);
        mAudioClient->Initialize(
            AUDCLNT_SHAREMODE_SHARED,
            AUDCLNT_STREAMFLAGS_LOOPBACK,
            length,
            0, mFormat.get(), NULL);
        testHR(hr);

        hr = mAudioClient->GetService(__uuidof(IAudioCaptureClient),
            (void**)mAudioCaptureClient.ReleaseAndGetAddressOf());
        testHR(hr);

        mTimer.setInterval(static_cast<int>(1000 / updateRate));
        mBuffer = std::unique_ptr<luna::SampleBuffer>(new luna::SampleBuffer(1 << 13, outputChannels));
    }

    void AudioCapture::start()
    {
        mAudioClient->Start();
        mTimer.start();
    }

    void AudioCapture::stop()
    {
        mTimer.stop();
        mAudioClient->Stop();
    }

    void AudioCapture::readSamples()
    {
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

            mBuffer->readFrom(reinterpret_cast<float *>(data), framesAvailable);

            mAudioCaptureClient->ReleaseBuffer(framesAvailable);
            hr = mAudioCaptureClient->GetNextPacketSize(&packetSize);
            testHR(hr);
        }

        emit samplesReady();
    }


    void AudioCapture::panic(const char * msg)
    {
        throw std::runtime_error(msg);
    }
}}
