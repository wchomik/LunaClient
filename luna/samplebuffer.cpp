#include "samplebuffer.h"

#include <cstring>

namespace luna {
    SampleBuffer::SampleBuffer(size_t size, int channelCount) :
        mSize(size * channelCount),
        mChannelCount(channelCount),
        mData(new float[mSize * 2]()),
        mPtr(mData.get())
    {}

    void SampleBuffer::readFrom(const float * src, size_t sampleCount)
    {
        size_t writeCount = sampleCount * mChannelCount;
        float * pNext = mPtr + writeCount;
        if(pNext >= mData.get() + mSize){
            pNext = mData.get();
            size_t copyCount = mSize - writeCount;
            memcpy(mData.get(), mPtr + writeCount, copyCount * sizeof(float));
            memcpy(mData.get() + copyCount, src, writeCount * sizeof(float));
            mPtr = mData.get();
        }else{
            memcpy(mPtr + mSize, src, writeCount * sizeof(float));
            mPtr += writeCount;
        }
    }

    SampleBuffer::Channel SampleBuffer::channel(int index)
    {
        return Channel(mPtr + index, mChannelCount);
    }
}
