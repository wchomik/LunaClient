#ifndef COMMAND_ENCODER_H
#define COMMAND_ENCODER_H

#include <cstdint>

#include <tls/ssl.hpp>

#include "serializer.h"

class command_encoder
{
public:
    command_encoder(tls::ssl * ssl);

    serializer & get_serializer() noexcept;
    void send();
private:
    using packet_size_t = uint16_t;
    static constexpr size_t BUFFER_SIZE = 1024;

    uint8_t m_buffer[BUFFER_SIZE];
    serializer m_serializer;
    tls::ssl * m_ssl;
};

#endif // COMMAND_ENCODER_H
