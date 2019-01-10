#ifndef LUNAAUDIOPROVIDER_H
#define LUNAAUDIOPROVIDER_H

#include <unordered_map>
#include <luna/interface/provider.h>

#include "audiocapture.h"
#include "fft.h"
#include "audiochannelprocessor.h"
#include "samplebuffer.h"

class AudioProvider : public luna::interface::Provider
{
public:
    AudioProvider();
    virtual ~AudioProvider();

    void getData(std::vector<luna::interface::Strand *> &strands) override;
private:
    std::unique_ptr<SampleBuffer> mBuffer;
    AudioCapture mAudioCapture;
    FFT mFFT;
    std::unordered_map<const luna::interface::Strand *, std::unique_ptr<AudioChannelProcessor>> mProcessors;

    void createAudioProcessor(const luna::interface::Strand * strand);
};


#endif // LUNAAUDIOPROVIDER_H
