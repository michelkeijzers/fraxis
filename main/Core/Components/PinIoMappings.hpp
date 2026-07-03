#pragma once
#include <cstdint>

class PinIoMappings
{
public:
    enum class EIdBit : uint8_t
    {
        Player1Up       = 8,
        Player1Down     = 9,
        Player1Left     = 11,
        Player1Right    = 14,
        Player1Button   = 10,
        Player1Led      = 4,

        Player2Up       = 12,
        Player2Down     = 2,
        Player2Left     = 1,
        Player2Right    = 0,
        Player2Button   = 15,
        Player2Led      = 3,

        SystemButton    = 13,
        PauseLed        = 5,
        SelectLed       = 6,
        SettingsLed     = 7
    };

    static uint8_t GetPort(EIdBit id);
    static uint8_t GetPin(EIdBit id);
};
