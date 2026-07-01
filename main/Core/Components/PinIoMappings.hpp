#pragma once

class PinIoMappings
{
public:
    static const uint8_t P1_UP_PORT     = 1;
    static const uint8_t P1_UP_PIN      = 0;
    static const uint8_t P1_DOWN_PORT   = 1;
    static const uint8_t P1_DOWN_PIN    = 1;
    static const uint8_t P1_LEFT_PORT   = 1;
    static const uint8_t P1_LEFT_PIN    = 3;
    static const uint8_t P1_RIGHT_PORT  = 1;
    static const uint8_t P1_RIGHT_PIN   = 6;
    static const uint8_t P1_BUTTON_PORT = 1;
    static const uint8_t P1_BUTTON_PIN  = 2;
    static const uint8_t P1_LED_PORT    = 0;
    static const uint8_t P1_LED_PIN     = 4;

    static const uint8_t P2_UP_PORT     = 1;
    static const uint8_t P2_UP_PIN      = 4;
    static const uint8_t P2_DOWN_PORT   = 1;
    static const uint8_t P2_DOWN_PIN    = 1;
    static const uint8_t P2_LEFT_PORT   = 0;
    static const uint8_t P2_LEFT_PIN    = 1;
    static const uint8_t P2_RIGHT_PORT  = 0;
    static const uint8_t P2_RIGHT_PIN   = 0;
    static const uint8_t P2_BUTTON_PORT = 1;
    static const uint8_t P2_BUTTON_PIN  = 7;
    static const uint8_t P2_LED_PORT    = 0;
    static const uint8_t P2_LED_PIN     = 3;

    static const uint8_t SYSTEM_BUTTON_PORT = 1;
    static const uint8_t SYSTEM_BUTTON_PIN  = 5;
    static const uint8_t PAUSE_LED_PORT     = 0;
    static const uint8_t PAUSE_LED_PIN      = 5;
    static const uint8_t SELECT_LED_PORT    = 0;
    static const uint8_t SELECT_LED_PIN     = 6;
    static const uint8_t SETTINGS_LED_PORT  = 0;
    static const uint8_t SETTINGS_LED_PIN   = 7;
};
