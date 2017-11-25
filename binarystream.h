#ifndef BINARYSTREAM_H
#define BINARYSTREAM_H

#include <memory>

class BinaryStream {
public:
    BinaryStream(size_t size);

    void write(const void * src, size_t count);
    template<typename T>
    BinaryStream & operator<<(const T & value);
    void reset();
    const char * data() const;
    size_t count() const;
private:
    std::unique_ptr<char[]> mBuffer;
    char * mPtr;
};

template<typename T>
BinaryStream & BinaryStream::operator <<(const T & value){
    write(reinterpret_cast<const void *>(&value), sizeof(T));
    return *this;
}

#endif // BINARYSTREAM_H
