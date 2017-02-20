#ifndef AUDIOCAPTURE_H
#define AUDIOCAPTURE_H

#include <memory>

#include <QObject>
#include <QTimer>

#include <wrl.h>
#include <Audioclient.h>
#include <mmdeviceapi.h>
#include "samplebuffer.h"

namespace luna { namespace audio {
    class AudioCapture : public QObject{
        Q_OBJECT
    public:
        explicit AudioCapture(QObject * parent = 0);
        ~AudioCapture();

        void configure(int outputChannels, float updateRate);
        luna::SampleBuffer * sampleBuffer(){ return mBuffer.get(); }
        int sampleRate(){ return mFormat->nSamplesPerSec; }
    public slots:
        void start();
        void stop();
    private slots:
        void readSamples();
    signals:
        void samplesReady();

    private:
        void panic(const char *msg = "");

        QTimer mTimer;
        std::unique_ptr<luna::SampleBuffer> mBuffer;
        float mUpdateRate;

        Microsoft::WRL::ComPtr<IMMDeviceEnumerator> mDevEnum;
        Microsoft::WRL::ComPtr<IMMDevice> mAudioDevice;
        Microsoft::WRL::ComPtr<IAudioClient> mAudioClient;
        Microsoft::WRL::ComPtr<IAudioCaptureClient> mAudioCaptureClient;
        typedef std::unique_ptr<WAVEFORMATEX, decltype(&CoTaskMemFree)> formatPtr_t;
        formatPtr_t mFormat;
    };
}}

#endif // AUDIOCAPTURE_H
