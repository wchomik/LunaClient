#ifndef SAMPLEBUFFER_H
#define SAMPLEBUFFER_H



namespace luna {
    class SampleBuffer
    {
    private:
        class Channel{
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
        ~SampleBuffer();
        size_t size() { return mSize; }
        void readFrom(float * src, size_t sampleCount);
        Channel channel(int index);

    private:
        size_t mSize;
        int mChannelCount;
        float * const mData;
        float * mPtr;
        float * begin(){ return mPtr; }
        float * end(){ return mPtr + mSize; }
    };
}

#endif // SAMPLEBUFFER_H
