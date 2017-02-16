#ifndef BINARYSTREAM_H
#define BINARYSTREAM_H

#include <cstring>

template<size_t size>
class BinaryStream {
public:
    BinaryStream();

    void write(const void * src, size_t count);
    template<typename T>
    BinaryStream & operator<<(const T & value);
    void reset();
    char * data();
    size_t count();
private:
    char mBuffer[size];
    char * mPtr;
};

template<size_t size>
BinaryStream<size>::BinaryStream() :
    mPtr(mBuffer)
{}

template<size_t size>
void BinaryStream<size>::write(const void * src, size_t count){
    memcpy(mPtr, src, count);
    mPtr += count;
}

template<size_t size>
template<typename T>
BinaryStream<size> & BinaryStream<size>::operator <<(const T & value){
    write(reinterpret_cast<const void *>(&value), sizeof(T));
    return *this;
}

template<size_t size>
void BinaryStream<size>::reset(){
    mPtr = mBuffer;
}

template<size_t size>
char * BinaryStream<size>::data(){
    return mBuffer;
}

template<size_t size>
size_t BinaryStream<size>::count(){
    return mPtr - mBuffer;
}

#endif // BINARYSTREAM_H
