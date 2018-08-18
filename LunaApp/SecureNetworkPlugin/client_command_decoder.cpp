#include "client_command_decoder.h"

#include "packets.h"
#include "client_handler.h"
#include "serializer.h"

client_command_decoder::client_command_decoder(client_handler * handler) :
    m_handler(handler)
{
}

void client_command_decoder::decode(serializer & s)
{
    uint8_t id;
    s >> id;
    switch (id) {
        case luna_configuration::id: {
            luna_configuration config;
            s >> config;
            m_handler->configuration_received(config);
            break;
        }
        case data_channel_configuration::id: {
            data_channel_configuration config;
            s >> config;
            m_handler->data_channel_opened(config);
            break;
        }
    }
}
