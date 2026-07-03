#include "PinIoMappings.hpp"

uint8_t PinIoMappings::GetPort(PinIoMappings::EId id)
{
    return ((uint16_t)id) >> 8;
}

uint8_t PinIoMappings::GetPin(PinIoMappings::EId id)
{
    return ((uint16_t)id) & 0xFF;
}

