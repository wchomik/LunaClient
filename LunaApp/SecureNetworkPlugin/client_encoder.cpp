#include "client_encoder.h"

#include "packets.h"
#include "serializer.h"

client_encoder::client_encoder(command_encoder * encoder) :
    m_command_encoder(encoder)
{
}

void client_encoder::request_configuration()
{
    uint8_t id = luna_configuration::id;
    m_command_encoder->get_serializer() << id;
    m_command_encoder->send();
}

void client_encoder::open_data_channel()
{
    uint8_t id = data_channel_configuration::id;
    m_command_encoder->get_serializer() << id;
    m_command_encoder->send();
}

void client_encoder::close_data_channel()
{
    uint8_t id = 2;
    m_command_encoder->get_serializer() << id;
    m_command_encoder->send();
}
