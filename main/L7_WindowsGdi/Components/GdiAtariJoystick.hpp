#pragma once

#include "../IGdiMouseInput.hpp"
#include "../../L3_Messages/Types.hpp"
#include <cstdint>
#include <Windows.h>
#include <string>

class GdiScreen;
class Mcp23017DeviceDriver;

class GdiAtariJoystick : public IGdiMouseInput
{
public:
    GdiAtariJoystick(
        GdiScreen& gdiScreen,
        Types::EJoystickId id,
        uint8_t bitNumberUp,
        uint8_t bitNumberRight,
        uint8_t bitNumberDown,
        uint8_t bitNumberLeft,
        uint8_t bitNumberButton,
        uint16_t x,
        uint16_t y,
        Mcp23017DeviceDriver& mcp23017DeviceDriver);
    ~GdiAtariJoystick();

    bool HitTest(
        int x, 
        int y) override;
    void OnMouseDown(
        int x, 
        int y) override;
    void OnMouseMove(
        int x, 
        int y) override;
    void OnMouseUp(
        int x, 
        int y) override;
    void Update(
        HDC* hdc);

private:
    HBRUSH BrushFor(
        bool active,
        bool hover);
    void DrawTriangle(
        HBRUSH brush,
        const POINT pts[3]);
    void DrawCircle(
        HBRUSH brush);

    enum class ESwitchBitNumber
    {
        Up      = 0,
        Right   = 1,
        Down    = 2,
        Left    = 3,
        Button  = 4
    };

    void SimulateBits();
    void UpdateHover(
        int mouseX,
        int mouseY);

    uint16_t D(
        uint16_t value) const;
    HBRUSH GetBrush(
        bool pressed);

    GdiScreen& _gdiScreen;
    Types::EJoystickId _id;
    uint8_t _bitNumberUp;
    uint8_t _bitNumberRight;
    uint8_t _bitNumberDown;
    uint8_t _bitNumberLeft;
    uint8_t _bitNumberButton;
    int _x;
    int _y;

    bool _pressed;
    /// @brief Bitmask of ESwitch
    uint16_t _pressedSwitches; 
    bool _hovered;
    /// @brief Bitmask of ESwitch
    uint16_t _hoveredSwitches; 

    Mcp23017DeviceDriver& _mcp23017DeviceDriver;

    HBRUSH _pressedBrush;
    HBRUSH _hoverBrush;
    HBRUSH _inactiveBrush;
    HPEN   _surroundingPen;
    HBRUSH _surroundingBrush;

    HDC* _hdc;
};
