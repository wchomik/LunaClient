#pragma once

#include <vector>

class SampleBuffer
{
public:
    class Channel{
    public:
        Channel(float * begin, size_t stride) :
            mBegin(begin), mStride(stride) {}
        float & operator[](size_t index){
            return mBegin[index * mStride];
        }
    private:
        float * const mBegin;
        const size_t mStride;
    };
    SampleBuffer(size_t size, unsigned channelCount);
    size_t size() const;
    void readFrom(const float * src, size_t sampleCount);
    Channel channel(unsigned index);
private:
    size_t mSize;
    unsigned mChannelCount;
    std::vector<float> mData;
    float * mPtr;
    float * begin(){ return mPtr; }
    float * end(){ return mPtr + mSize; }
};
