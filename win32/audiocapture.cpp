#include "audiocapture.h"

#include <comdef.h>
#include <QDebug>

namespace luna { namespace audio {
    AudioCapture::AudioCapture(QObject * parent) :
        QObject(parent),
        mTimer(this),
        mDevEnum(nullptr),
        mAudioDevice(nullptr),
        mAudioClient(nullptr),
        mFormat(nullptr),
        mAudioCaptureClient(nullptr)
    {
        QObject::connect(&mTimer, &QTimer::timeout, this, &AudioCapture::readSamples);
        CoInitializeEx(0, COINIT_MULTITHREADED);
    }

    AudioCapture::~AudioCapture()
    {
        cleanup();
        CoUninitialize();
    }

    void AudioCapture::configure(int outputChannels, float updateRate)
    {
        cleanup();
        HRESULT hr;
        hr = CoCreateInstance(
            __uuidof(MMDeviceEnumerator),
            NULL,
            CLSCTX_ALL,
            __uuidof(IMMDeviceEnumerator),
            (void**)&mDevEnum);
        fail(hr);

        hr = mDevEnum->GetDefaultAudioEndpoint(eRender, eMultimedia, &mAudioDevice);
        fail(hr);

        mAudioDevice->Activate(__uuidof(IAudioClient), CLSCTX_ALL, NULL, (void**)&mAudioClient);
        fail(hr);

        hr = mAudioClient->GetMixFormat(&mFormat);
        fail(hr);

        // TODO add channel mixing
        if(mFormat->nChannels != outputChannels) panic();
        // TODO support non floating point formats
        if(mFormat->wFormatTag != WAVE_FORMAT_IEEE_FLOAT){
            if(mFormat->wFormatTag != WAVE_FORMAT_EXTENSIBLE) panic();
            WAVEFORMATEXTENSIBLE * format = reinterpret_cast<WAVEFORMATEXTENSIBLE *>(mFormat);
            if(format->SubFormat != KSDATAFORMAT_SUBTYPE_IEEE_FLOAT) panic();
        }

        REFERENCE_TIME length = static_cast<REFERENCE_TIME>(10000000 * 1.2f / updateRate);
        mAudioClient->Initialize(
            AUDCLNT_SHAREMODE_SHARED,
            AUDCLNT_STREAMFLAGS_LOOPBACK,
            length,
            0, mFormat, NULL);
        fail(hr);

        hr = mAudioClient->GetService(__uuidof(IAudioCaptureClient), (void**)&mAudioCaptureClient);
        fail(hr);

        mTimer.setInterval(static_cast<int>(1000 / updateRate));
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

        while (packetSize != 0)
        {
            uint32_t framesAvailable;
            uint8_t * data;
            DWORD flags;
            hr = mAudioCaptureClient->GetBuffer(&data, &framesAvailable, &flags, nullptr, nullptr);

            // TODO copy stuff
            mAudioCaptureClient->ReleaseBuffer(framesAvailable);
            hr = mAudioCaptureClient->GetNextPacketSize(&packetSize);
        }

        emit samplesReady();
    }


    void AudioCapture::cleanup()
    {
        release(mAudioCaptureClient);
        free(mFormat);
        release(mAudioClient);
        release(mAudioDevice);
        release(mDevEnum);
    }

    void AudioCapture::fail(long hr)
    {
        if(FAILED(hr)) {
            _com_error err(hr);
            LPCTSTR errMsg = err.ErrorMessage();
            char msg[128];
            wcstombs(msg, errMsg, 128);
            panic(msg);
        }
    }

    void AudioCapture::panic(const char * msg)
    {
        cleanup();
        throw std::runtime_error(msg);
    }
}}
