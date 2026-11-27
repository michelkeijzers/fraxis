#pragma once

#include "../../M30_Messages/Types.hpp"
#include <cstdint>
#include <Windows.h>
#include <string>

namespace M50::I2c
{
    class Mcp23017DeviceModel;
}

namespace M90::Assert
{
    class IAssert;
}

namespace M70::Components
{
    class GdiLed
    {
    public:
        enum class EColor : uint8_t
        {
            Red,
            Green
        };

        GdiLed(
            M90::Assert::IAssert& assert,
            std::string_view text,
            EColor color,
            uint8_t bitNumber,
            uint16_t x,
            uint16_t y);
    
        ~GdiLed();

        M50::I2c::Mcp23017DeviceModel& GetDeviceModel();

        void SetDeviceModel(
            M50::I2c::Mcp23017DeviceModel& deviceModel);

        void Update(HDC* hdc);

    private:
        M90::Assert::IAssert& _assert;

        uint16_t D(
            uint16_t value) const;
        
        HBRUSH GetBrush(
            bool on);

        std::string _text;
        
        EColor _color;
        
        uint8_t _bitNumber;
        
        uint16_t _x;
        
        uint16_t _y;

        HFONT _font;
        
        HBRUSH _bezelBrush;

        HPEN   _bezelPen;

        HBRUSH _offBrush;

        HBRUSH _greenBrush;

        HBRUSH _redBrush;

        M50::I2c::Mcp23017DeviceModel* _deviceModel;
    };
}
