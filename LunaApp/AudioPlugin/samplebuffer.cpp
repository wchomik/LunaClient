#include "samplebuffer.h"

#include <cstring>

SampleBuffer::SampleBuffer(size_t size, unsigned channelCount) :
    mSize(size * channelCount),
    mChannelCount(channelCount),
    mData(mSize * 2),
    mPtr(mData.data())
{}

size_t SampleBuffer::size() const {
    return mSize;
}

void SampleBuffer::readFrom(const float * src, size_t sampleCount) {
    const size_t writeCount = sampleCount * mChannelCount;
    float * pNext = mPtr + writeCount;
    if(pNext >= mData.data() + mSize){
        pNext = mData.data();
        const size_t copyCount = mSize - writeCount;
        memcpy(mData.data(), mPtr + writeCount, copyCount * sizeof(float));
        memcpy(mData.data() + copyCount, src, writeCount * sizeof(float));
        mPtr = mData.data();
    }else{
        memcpy(mPtr + mSize, src, writeCount * sizeof(float));
        mPtr += writeCount;
    }
}

SampleBuffer::Channel SampleBuffer::channel(unsigned index) {
    return Channel(mPtr + index, mChannelCount);
}

