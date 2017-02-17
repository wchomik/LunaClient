#ifndef AUDIOCAPTURE_H
#define AUDIOCAPTURE_H

#include <QObject>
#include <QTimer>

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
    public slots:
        void start();
        void stop();
    private slots:
        void readSamples();
    signals:
        void samplesReady();

    private:
        template<typename T>
        static void release(T *& obj){
            if(obj != nullptr){
                obj->Release();
                obj = nullptr;
            }
        }
        template<typename T>
        static void free(T *& obj){
            if(obj != nullptr){
                CoTaskMemFree(obj);
                obj = nullptr;
            }
        }

        void cleanup();
        void fail(long hr);
        void panic(const char *msg = "");

        QTimer mTimer;
        luna::SampleBuffer * mBuffer;
        float mUpdateRate;
        IMMDeviceEnumerator * mDevEnum;
        IMMDevice * mAudioDevice;
        IAudioClient * mAudioClient;
        WAVEFORMATEX * mFormat;
        IAudioCaptureClient * mAudioCaptureClient;
    };
}}

#endif // AUDIOCAPTURE_H
