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
    /// @brief: bit numbers in MCP
    struct BitNumbers
    {
        uint8_t Up;
        uint8_t Right;
        uint8_t Down;
        uint8_t Left;
        uint8_t Button;
    };

    /// @brief: bit numbers for internal usage (and TriggerSwitch)
    enum class ESwitchBitNumber
    {
        Up = 0,
        Right = 1,
        Down = 2,
        Left = 3,
        Button = 4,

        /// @brief Only used for keyboard support, unused @todo: check if can be removed
        None = 99
    };

    GdiAtariJoystick(
        GdiScreen& gdiScreen,
        Types::EJoystickId id,
        BitNumbers bitNumbers,
        uint16_t x,
        uint16_t y);
    ~GdiAtariJoystick();

    Mcp23017DeviceDriver& GetDeviceDriver();
        
    void SetDeviceDriver(
        Mcp23017DeviceDriver& deviceDriver);

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

    void TriggerSwitch(
        ESwitchBitNumber bitNumber,
        bool state);

private:
    HBRUSH BrushFor(
        bool active,
        bool hover);
    void DrawTriangle(
        HBRUSH brush,
        const POINT pts[3]) const;
    void DrawCircle(
        HBRUSH brush) const;

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
    BitNumbers _bitNumbers;
    int _x;
    int _y;

    bool _pressed;
    /// @brief Bitmask of ESwitch
    uint16_t _pressedSwitches; 
    bool _hovered;
    /// @brief Bitmask of ESwitch
    uint16_t _hoveredSwitches; 

    Mcp23017DeviceDriver* _deviceDriver;

    HBRUSH _pressedBrush;
    HBRUSH _hoverBrush;
    HBRUSH _inactiveBrush;
    HPEN   _surroundingPen;
    HBRUSH _surroundingBrush;

    HDC* _hdc;
};
