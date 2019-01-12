#include "FFT.hpp"

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
    mFftPlan = fftwf_plan_dft_r2c_1d(
                   static_cast<int>(size),
                   reinterpret_cast<float *>(mInput.data()),
                   reinterpret_cast<fftwf_complex *>(mOutput.data()), \
                   FFTW_ESTIMATE);

    const float alpha = 0.54f;
    const float beta = 1.0f - alpha;

    mWindow = alpha - Eigen::ArrayXf::LinSpaced(mSize, 0, static_cast<float>(2 * M_PI * (mSize - 1) / (mSize))).cos()* beta;
}

FFT::~FFT() {
    fftwf_destroy_plan(mFftPlan);
}

void FFT::compute() {
    mInput = mInput * mWindow;

    fftwf_execute(mFftPlan);
    if (mFlags & magnitude) {
        mMagnitudes = mOutput.abs() * mScale;
    }
    if (mFlags & phase) {
        mPhases = mOutput.arg();
    }
}

Eigen::ArrayXf & FFT::input() {
    return mInput;
}

const Eigen::ArrayXf & FFT::magnitudes() const  {
    return mMagnitudes;
}

const Eigen::ArrayXf & FFT::phases() const {
    return mPhases;
}

size_t FFT::size() const {
    return mSize;
}
