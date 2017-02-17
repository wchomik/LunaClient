#ifndef FFT_H
#define FFT_H

#include <fftw3.h>
#include <Eigen/Core>

namespace luna { namespace audio {
    class FFT
    {
    public:
        enum Flag {
            magnitude = 1 << 0,
            phase = 1 << 1,
        };
        FFT(size_t size, Flag flag);
        ~FFT();
        void compute();
        Eigen::ArrayXf & input() { return mInput; }
        const Eigen::ArrayXf & magnitudes() { return mMagnitudes; }
        const Eigen::ArrayXf & phases() { return mPhases; }
    private:
        size_t mSize;
        float mScale;
        Flag mFlags;
        Eigen::ArrayXf mInput;
        Eigen::ArrayXf mWindow;
        Eigen::ArrayXcf mOutput;
        Eigen::ArrayXf mMagnitudes;
        Eigen::ArrayXf mPhases;
        fftwf_plan mFftPlan;
    };
}}

#endif // FFT_H
