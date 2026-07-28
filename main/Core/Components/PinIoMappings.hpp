#pragma once
#include <cstdint>

class PinIoMappings
{
public:
    static uint8_t GetPort(EIdBit id);
    static uint8_t GetPin(EIdBit id);
};
