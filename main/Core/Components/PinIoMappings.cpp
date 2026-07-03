#include "PinIoMappings.hpp"

uint8_t PinIoMappings::GetPort(PinIoMappings::EIdBit idBit)
{
    return ((uint16_t)idBit) >= 8 ? 1 : 0;
}

uint8_t PinIoMappings::GetPin(PinIoMappings::EIdBit idBit)
{
    return ((uint16_t)idBit >= 0x100) ? ((uint16_t)idBit) >> 8 : (uint16_t)idBit;
}

