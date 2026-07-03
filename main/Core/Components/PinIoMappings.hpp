#pragma once
#include <cstdint>

class PinIoMappings
{
public:
    enum class EId : uint16_t
    {
        Player1Up       = (1u << 8) | 0u, // port 1, pin 0
        Player1Down     = (1u << 8) | 1u,
        Player1Left     = (1u << 8) | 3u,
        Player1Right    = (1u << 8) | 6u,
        Player1Button   = (1u << 8) | 2u,
        Player1Led      = (0u << 8) | 4u,

        Player2Up       = (1u << 8) | 4u,
        Player2Down     = (1u << 8) | 1u,
        Player2Left     = (0u << 8) | 1u,
        Player2Right    = (0u << 8) | 0u,
        Player2Button   = (1u << 8) | 7u,
        Player2Led      = (0u << 8) | 3u,

        SystemButton    = (1u << 8) | 5u,
        PauseLed        = (0u << 8) | 5u,
        SelectLed       = (0u << 8) | 6u,
        SettingsLed     = (0u << 8) | 7u
    };

    static uint8_t GetPort(EId id);
    static uint8_t GetPin(EId id);
};
