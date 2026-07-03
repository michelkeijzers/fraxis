#include "PinIoMappings.hpp"

uint8_t PinIoMappings::GetPort(PinIoMappings::EIdBit idBit)
{
    return ((uint8_t)idBit) >= 8 ? 1 : 0;
}

uint8_t PinIoMappings::GetPin(PinIoMappings::EIdBit idBit)
{
    return ((uint8_t) idBit) % 8;
}

