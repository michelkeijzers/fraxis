#pragma once

#include "../IGdiMouseInput.hpp"
#include <cstdint>
#include <Windows.h>
#include <string>

class Mcp23017DeviceDriver;

class GdiButton : public IGdiMouseInput
{
public:
    GdiButton(
        std::string_view text,
        uint8_t bitNumber,
        int x,
        int y);
    ~GdiButton();

    Mcp23017DeviceDriver& GetMcp23017DeviceDriver();

    void SetMcp23017DeviceDriver(
        Mcp23017DeviceDriver& mcp23017DeviceDriver);

    bool HitTest(int x, int y) override;
    void OnMouseDown(int x, int y) override;
    void OnMouseMove(int x, int y) override;
    void OnMouseUp(int x, int y) override;
    void Update(HDC* hdc);

private:
    void SimulateBit(
        bool on);
    uint16_t D(
        uint16_t value) const;
    HBRUSH GetBrush(
        bool pressed);

    std::string _text;
    uint8_t _bitNumber;
    int _x;
    int _y;

    bool _pressed;
    bool _hovered;

    HFONT _font;
    HBRUSH _normalBrush;
    HBRUSH _hoverBrush;
    HBRUSH _pressedBrush;
    HPEN _borderPen;

    Mcp23017DeviceDriver* _mcp23017DeviceDriver;
};
