#ifndef CLIENT_ENCODER_H
#define CLIENT_ENCODER_H

#include <tls/ssl.hpp>

#include "command_encoder.h"

class client_encoder
{
public:
    client_encoder(command_encoder * encoder);

    void request_configuration();
    void open_data_channel();
    void close_data_channel();
private:
    command_encoder * m_command_encoder;
};

#endif // CLIENT_ENCODER_H
