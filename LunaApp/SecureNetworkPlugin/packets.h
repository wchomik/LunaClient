#ifndef PACKETS_H
#define PACKETS_H

#include <vector>
#include <cstdint>

#include "serializer.h"

struct point_millimeters {
    int x, y, z;
};

enum class bit_depth : uint8_t {
    integer_8_bits = 0,
    integer_16_bits = 1,
};

struct strand_configuration {
    //ColorSpace colorSpace;
    uint32_t colorChannels;
    uint32_t count;
    point_millimeters begin;
    point_millimeters end;
    bit_depth pixel_bit_depth;
};

struct luna_configuration {
    static constexpr uint8_t id = 0;
    std::vector<strand_configuration> strands;
};

template<>
inline serializer & operator>>(serializer & stream, luna_configuration & config) {
    stream >> config.strands;
    return stream;
}

template<>
inline serializer & operator<<(serializer & stream, luna_configuration const & config) {
    stream << config.strands;
    return stream;
}

struct data_channel_configuration {
    static constexpr uint8_t id = 1;
    uint16_t port;
    std::vector<uint8_t> shared_key;
};

template<>
inline serializer & operator>>(serializer & stream, data_channel_configuration & config) {
    stream >> config.port;
    stream >> config.shared_key;
    return stream;
}

template<>
inline serializer & operator<<(serializer & stream, data_channel_configuration const & config) {
    stream << config.port;
    stream << config.shared_key;
    return stream;
}


#endif // PACKETS_H
