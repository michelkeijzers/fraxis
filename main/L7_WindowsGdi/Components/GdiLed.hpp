#pragma once

#include "../../L3_Messages/Types.hpp"
#include <cstdint>
#include <Windows.h>
#include <string>

class Mcp23017DeviceModel;

class GdiLed
{
public:
    enum class EColor { Red, Green };

    GdiLed(
        std::string_view text,
        EColor color,
        uint8_t bitNumber,
        uint16_t x,
        uint16_t y);
    ~GdiLed();

    Mcp23017DeviceModel& GetDeviceModel();

    void SetDeviceModel(
        Mcp23017DeviceModel& deviceModel);

    void Update(HDC* hdc);

private:
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

    Mcp23017DeviceModel* _deviceModel;
};


