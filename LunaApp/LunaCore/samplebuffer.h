#ifndef SAMPLEBUFFER_H
#define SAMPLEBUFFER_H

#include <memory>
#include "lunacore_global.h"

namespace luna {
    class LUNACORESHARED_EXPORT SampleBuffer
    {
    private:
        class LUNACORESHARED_EXPORT Channel{
        public:
            Channel(float * begin, int stride) :
                mBegin(begin), mStride(stride) {}
            float & operator[](size_t index){
                return mBegin[index * mStride];
            }
        private:
            float * const mBegin;
            const int mStride;
        };
    public:
        SampleBuffer(size_t size, int channelCount);
        size_t size() { return mSize; }
        void readFrom(const float * src, size_t sampleCount);
        Channel channel(int index);

    private:
        size_t mSize;
        int mChannelCount;
        std::unique_ptr<float[]> mData;
        float * mPtr;
        float * begin(){ return mPtr; }
        float * end(){ return mPtr + mSize; }
    };
}

#endif // SAMPLEBUFFER_H
