#include "binarystream.h"

#include <cstring>

BinaryStream::BinaryStream(size_t size) :
    mBuffer(std::make_unique<char[]>(size)),
    mPtr(mBuffer.get())
{}

void BinaryStream::write(const void * src, size_t count){
    memcpy(mPtr, src, count);
    mPtr += count;
}

void BinaryStream::reset(){
    mPtr = mBuffer.get();
}

const char * BinaryStream::data() const {
    return mBuffer.get();
}

size_t BinaryStream::count() const {
    return static_cast<size_t>(mPtr - mBuffer.get());
}
