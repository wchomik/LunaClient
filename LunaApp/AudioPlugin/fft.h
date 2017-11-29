#ifndef FFT_H
#define FFT_H

#include <fftw3.h>
#include <Eigen/Core>

class FFT
{
public:
    enum Flag {
        none = 0,
        magnitude = 1 << 0,
        phase = 1 << 1,
    };
    FFT(size_t size, Flag flag);
    ~FFT();
    void compute();
    Eigen::ArrayXf & input();
    const Eigen::ArrayXf & magnitudes() const;
    const Eigen::ArrayXf & phases() const;
    size_t size() const;
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

#endif // FFT_H
