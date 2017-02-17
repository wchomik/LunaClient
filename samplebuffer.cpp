#include "samplebuffer.h"

#include <cstring>

namespace luna {
    SampleBuffer::SampleBuffer(size_t size, int channelCount) :
        mSize(size * channelCount),
        mChannelCount(channelCount),
        mData(new float[mSize * 2]),
        mPtr(mData)
    {}

    SampleBuffer::~SampleBuffer()
    {
        delete[] mData;
    }

    void SampleBuffer::readFrom(float * src, size_t sampleCount)
    {
        size_t writeCount = sampleCount * mChannelCount;
        float * pNext = mPtr + writeCount;
        if(pNext > mData + mSize){
            pNext = mData;
            size_t copyCount = mSize - writeCount;
            memcpy(mData, mPtr + writeCount, copyCount);
            memcpy(mData + copyCount, src, writeCount);
            mPtr = mData;
        }else{
            memcpy(mPtr + mSize, src, writeCount * sizeof(float));
            mPtr += writeCount;
        }
    }

    SampleBuffer::Channel SampleBuffer::channel(int index)
    {
        return Channel(mPtr + index, mPtr + index + mSize, mChannelCount);
    }
}
