#pragma once

#include <cstdint>

class serializer;

class command_decoder
{
public:
    virtual ~command_decoder() = default;

    virtual void decode(serializer & s) = 0;
};
