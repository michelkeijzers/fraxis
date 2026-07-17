#pragma once
#pragma pack(push, 1)

#include <cstdint>

class Message
{
public:
    enum class EId : uint8_t
    {
        LedStrip_Initialize,
        LedStrip_BufferReady,

        I2c_Initialize,
        
        Lcd1602Display_Initialize,
        Lcd1602Display_TextLines,

        Tm1637_Initialize,
        Tm1637_Time,
        Tm1637_Value
    };

    EId id;

    struct Lcd1602Display_TextLines_Parameters
    {
        char line1[16];
        char line2[16];
    };


    enum class ETm1637Id : uint8_t
    {
        CentralPanel    = 0,
        Player1         = 1,
        Player2         = 2
    };

    struct Tm1637_Initialize_Parameters
    {
        ETm1637Id id;
    };

    struct Tm1637_Time_Parameters
    {
        ETm1637Id id;
        uint8_t first;
        uint8_t second;
    };

    struct Tm1637_Value_Parameters
    {
        ETm1637Id id;
        uint32_t value;
    };

    union 
    {
        Lcd1602Display_TextLines_Parameters lcd1602Display_TextLines_Parameters;
        Tm1637_Initialize_Parameters        tm1637_Initialize_Parameters;
        Tm1637_Time_Parameters              tm1637_Time_Parameters;
        Tm1637_Value_Parameters             tm1637_Value_Parameters;
    };
};

#pragma pack(pop)
