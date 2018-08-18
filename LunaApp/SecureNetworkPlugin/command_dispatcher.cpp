#include "command_dispatcher.h"

#include "command_decoder.h"
#include "serializer.h"

command_dispatcher::command_dispatcher(command_decoder * decoder) :
    m_decoder(decoder),
    m_begin_pointer(m_buffer),
    m_end_pointer(m_buffer)
{
}

void command_dispatcher::dispatch(uint8_t const * buffer, size_t size)
{
    copy_to_buffer(buffer, size);

    while (sizeof(payload_size_t) <= occupied_space()) {
        serializer deserializer(m_begin_pointer, occupied_space());
        payload_size_t payload_size;
        deserializer >> payload_size;

        if(payload_size + sizeof(payload_size_t) <= occupied_space()) {
            m_decoder->decode(deserializer);
            m_begin_pointer += payload_size + sizeof(payload_size_t);
        }
    }
}

void command_dispatcher::copy_to_buffer(uint8_t const * buffer, size_t size)
{
    auto available_space = static_cast<size_t>(m_buffer + BUFFER_SIZE - m_end_pointer);

    if (size > available_space) {
        available_space = BUFFER_SIZE - occupied_space();
        if (size > available_space) {
            throw std::runtime_error("Insufficient space in command_dispatcher");
        } else {
            memmove(m_buffer, m_begin_pointer, occupied_space());
            m_end_pointer = m_buffer + occupied_space();
            m_begin_pointer = m_buffer;
        }
    }

    memcpy(m_end_pointer, buffer, size);
    m_end_pointer += size;
}

size_t command_dispatcher::occupied_space() const noexcept
{
    return static_cast<size_t>(m_end_pointer - m_begin_pointer);
}
