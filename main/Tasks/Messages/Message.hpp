#pragma once

#include <cstdint>

class Message
{
public:
    enum class EId
    {
        LedStrip_Initialize,
        LedStrip_BufferReady,

        I2c_Initialize,
        
        Lcd1602Display_Initialize,
        Lcd1602Display_TextLines
    };

    EId id;

    struct Lcd1602Display_TextLines_Parameters
    {
        char line1[16];
        char line2[16];
    };

    union 
    {
        Lcd1602Display_TextLines_Parameters lcd1602Display_TextLines_Parameters;
    };
};
