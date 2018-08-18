#pragma once

#include <cstdint>

#include <tls/ssl.hpp>

#include <address.h>

class command_decoder;

class command_dispatcher
{
public:
    command_dispatcher(command_decoder * decoder);

    void dispatch(uint8_t const * buffer, size_t size);
private:
    void copy_to_buffer(uint8_t const * buffer, size_t size);
    size_t occupied_space() const noexcept;

    using payload_size_t = uint16_t;

    static constexpr size_t BUFFER_SIZE = 1024;

    command_decoder * m_decoder;

    uint8_t m_buffer[BUFFER_SIZE];
    uint8_t * m_begin_pointer;
    uint8_t * m_end_pointer;
};
