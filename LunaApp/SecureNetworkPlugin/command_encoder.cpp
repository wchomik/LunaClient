#include "command_encoder.h"

command_encoder::command_encoder(tls::ssl * ssl) :
    m_serializer(m_buffer, BUFFER_SIZE),
    m_ssl(ssl)
{
    m_serializer << static_cast<packet_size_t>(0);
}

serializer & command_encoder::get_serializer() noexcept
{
    return m_serializer;
}

void command_encoder::send()
{
    auto size = m_serializer.size();

    m_serializer.reset();
    m_serializer << static_cast<packet_size_t>(size - sizeof(packet_size_t));

    m_ssl->write(m_buffer, size);
}
