#pragma once

#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <vector>


class serializer
{
public:
    explicit serializer(uint8_t * buffer, size_t size) :
        m_buffer(buffer),
        m_pointer(m_buffer),
        m_end(m_pointer + size)
    {
    }

    void write(uint8_t const * source, size_t size)
    {
        if (m_pointer + size > m_end) {
            throw std::out_of_range("Attempting to write beyond allowed serializer range.");
        }
        memcpy(m_pointer, source, size);
        m_pointer += size;
    }

    void read(uint8_t * destination, size_t size)
    {
        if (m_pointer + size > m_end) {
            throw std::out_of_range("Attempting to read beyond allowed serializer range.");
        }
        memcpy(destination, m_pointer, size);
        m_pointer += size;
    }

    uint8_t const * data() const noexcept { return m_buffer; }
    size_t size() const noexcept { return static_cast<size_t>(m_pointer - m_buffer); }
    void reset() noexcept { m_pointer = m_buffer; }
private:
    uint8_t * m_buffer;
    uint8_t * m_pointer;
    uint8_t * m_end;
};


template<typename T>
serializer & operator<<(serializer & stream, T const & object) {
    auto source = reinterpret_cast<uint8_t const *>(&object);
    stream.write(source, sizeof(T));
    return stream;
}

template<typename T>
serializer & operator>>(serializer & stream, T & object) {
    auto source = reinterpret_cast<uint8_t *>(&object);
    stream.read(source, sizeof(T));
    return stream;
}

template<typename T>
serializer & operator<<(serializer & stream, std::vector<T> const & vector) {
    auto size = static_cast<uint32_t>(vector.size());
    stream << size;
    for(auto && item : vector) {
        stream << item;
    }
    return stream;
}

template<typename T>
serializer & operator>>(serializer & stream, std::vector<T> & vector) {
    vector.clear();
    uint16_t size;
    stream >> size;
    vector.reserve(size);
    for (uint16_t i = 0; i < size; ++i) {
        vector.emplace_back();
        stream >> vector.back();
    }
    return stream;
}

