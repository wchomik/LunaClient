#ifndef LUNAAUDIOPROVIDER_H
#define LUNAAUDIOPROVIDER_H

#include <unordered_map>
#include <provider.h>

#include "audiocapture.h"
#include "fft.h"
#include "audiochannelprocessor.h"
#include "samplebuffer.h"

class AudioProvider : public luna::Provider
{
public:
    AudioProvider();
    virtual ~AudioProvider();

    void getData(std::vector<luna::Strand *> &strands) override;
private:
    std::unique_ptr<SampleBuffer> mBuffer;
    AudioCapture mAudioCapture;
    FFT mFFT;
    std::unordered_map<const luna::Strand *, std::unique_ptr<AudioChannelProcessor>> mProcessors;

    void createAudioProcessor(const luna::Strand * strand);
};


#endif // LUNAAUDIOPROVIDER_H
