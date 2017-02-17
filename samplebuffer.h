#ifndef SAMPLEBUFFER_H
#define SAMPLEBUFFER_H



namespace luna {
    class SampleBuffer
    {
    private:
        class Channel{
        public:
            Channel(float * begin, float * end, int stride) :
                mBegin(begin), mEnd(end), mStride(stride) {}
            float * begin(){ return mBegin; }
            float * end(){ return mEnd; }
            float & operator[](size_t index){
                return mBegin[index * mStride];
            }
        private:
            float * mBegin;
            float * mEnd;
            int mStride;
        };
    public:
        explicit SampleBuffer(size_t size, int channelCount);
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
