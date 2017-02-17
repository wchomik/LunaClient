#include "fft.h"

namespace luna { namespace audio {
    FFT::FFT(size_t size, Flag flag) :
        mSize(size),
        mScale(1.0f / size),
        mFlags(flag),
        mInput(size),
        mWindow(size),
        mOutput(size / 2 + 1),
        mMagnitudes(size / 2 + 1),
        mPhases(size / 2 + 1)
    {
        mFftPlan = fftwf_plan_dft_r2c_1d(size,
            reinterpret_cast<float *>(mInput.data()),
            reinterpret_cast<fftwf_complex *>(mOutput.data()),\
            FFTW_ESTIMATE);
    }

    FFT::~FFT()
    {
        fftwf_destroy_plan(mFftPlan);
    }

    void FFT::compute()
    {
        fftwf_execute(mFftPlan);
        if(mFlags & magnitude){
            mMagnitudes = mOutput.abs() * mScale;
        }
        if(mFlags & phase){
            mPhases = mOutput.arg();
        }
    }
}}
