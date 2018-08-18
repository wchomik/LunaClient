#pragma once

#include "packets.h"

class client_handler
{
public:
    virtual ~client_handler() = default;

    virtual void configuration_received(luna_configuration const & luna_configuration) = 0;
    virtual void data_channel_opened(data_channel_configuration const & channel) = 0;
    virtual void data_channel_closed() = 0;
};
