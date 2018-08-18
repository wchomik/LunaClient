#ifndef CLIENT_COMMAND_DECODER_H
#define CLIENT_COMMAND_DECODER_H

#include "command_decoder.h"

class client_handler;

class client_command_decoder : public command_decoder
{
public:
    explicit client_command_decoder(client_handler * handler);
    void decode(serializer & s) override;
private:
    client_handler * m_handler;
};

#endif // CLIENT_COMMAND_DECODER_H
