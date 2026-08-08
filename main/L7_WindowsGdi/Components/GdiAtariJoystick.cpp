#include "GdiAtariJoystick.hpp"
#include "../GdiScreen.hpp" 
#include "../../L5_DeviceModels/Mcp23017/Mcp23017DeviceModel.hpp"
#include "../../L6_DeviceDrivers/Mcp23017/Mcp23017DeviceDriver.hpp"
#include "../../L6_DeviceDrivers/I2c/I2cDeviceDriver.hpp"
#include "../../L8_Services/I2c/WindowsI2c.hpp"
#include "../../L9_Utilities/Log/Log.hpp"
#include "../../L9_Utilities/Assert/Assert.hpp"
#include "../../L9_Utilities/Math/BitUtilities.hpp"
#include "Windows.h"
#include <array>

/// @brief Width of one segment (i.e. arrow or button)
const int WIDTH = 35;

/// @brief Height of one segment (i.e. arrow or button)
const int HEIGHT = 35;

GdiAtariJoystick::GdiAtariJoystick(
    GdiScreen& gdiScreen,
    Types::EJoystickId id,
    uint8_t bitNumberUp,
    uint8_t bitNumberRight,
        uint8_t bitNumberDown,
        uint8_t bitNumberLeft,
        uint8_t bitNumberButton,
        uint16_t x,
        uint16_t y)
:   _gdiScreen(gdiScreen),
    _id(id),
    _bitNumberUp(bitNumberUp),
    _bitNumberRight(bitNumberRight),
    _bitNumberDown(bitNumberDown),
    _bitNumberLeft(bitNumberLeft),
    _bitNumberButton(bitNumberButton),
    _x(x),
    _y(y),
    _pressed(false),
    _pressedSwitches(0),
    _hovered(false),
    _hoveredSwitches(0),
    _hdc(nullptr)
{
    _pressedBrush = CreateSolidBrush(RGB(0, 255, 0));
    _hoverBrush = CreateSolidBrush(RGB(0, 150, 0));
    _inactiveBrush = CreateSolidBrush(RGB(140, 140, 140));
    _surroundingPen = CreatePen(PS_SOLID, 2, RGB(140, 140, 140));
    _surroundingBrush = CreateSolidBrush(RGB(0, 0, 0));
}

GdiAtariJoystick::~GdiAtariJoystick()
{
    DeleteObject(_pressedBrush);
    DeleteObject(_hoverBrush);
    DeleteObject(_inactiveBrush);
    DeleteObject(_surroundingPen);
    DeleteObject(_surroundingBrush);
}

Mcp23017DeviceDriver& GdiAtariJoystick::GetMcp23017DeviceDriver()
{
    return *_mcp23017DeviceDriver;
}

void GdiAtariJoystick::SetMcp23017DeviceDriver(
    Mcp23017DeviceDriver& mcp23017DeviceDriver)
{
    _mcp23017DeviceDriver = &mcp23017DeviceDriver;
}

uint16_t GdiAtariJoystick::D(
    uint16_t value) const
{
    return value * 2;
}

bool GdiAtariJoystick::HitTest(int x, int y)
{
    return
        x >= _x && x <= _x + D(WIDTH) * 3 &&
        y >= _y && y <= _y + D(HEIGHT) * 3;
}

void GdiAtariJoystick::OnMouseDown(int x, int y)
{
    if (HitTest(x, y))
    {
        int width = D(WIDTH);
        int height = D(HEIGHT);

        uint8_t newPressedSwitches = 0;

        int cx = _x + width * 3 / 2;
        int cy = _y + height * 3 / 2;
        int dx = x - cx;
        int dy = y - cy;

        // Button
        if ((abs(dx) < width / 2) && abs(dy) < height / 2)
            newPressedSwitches |= 1 << (uint8_t)ESwitchBitNumber::Button; // NOSONAR: ESP32 prefers uint8_t

        // Directions
        if (dy < -height / 2)
            newPressedSwitches |= 1 << (uint8_t)ESwitchBitNumber::Up; // NOSONAR: ESP32 prefers uint8_t
        else if (dy > height / 2)
            newPressedSwitches |= 1 << (uint8_t)ESwitchBitNumber::Down; // NOSONAR: ESP32 prefers uint8_t

        if (dx < -width / 2)
            newPressedSwitches |= 1 << (uint8_t)ESwitchBitNumber::Left; // NOSONAR: ESP32 prefers uint8_t
        else if (dx > width / 2)
            newPressedSwitches |= 1 << (uint8_t)ESwitchBitNumber::Right; // NOSONAR: ESP32 prefers uint8_t

        if (newPressedSwitches != _pressedSwitches)
        {
            _pressedSwitches = newPressedSwitches;
            SimulateBits();
        }
        MarkDirty();
    }
}

void GdiAtariJoystick::OnMouseMove(int x, int y)
{
    UpdateHover(x, y);

    // Drag logic only when pressed
    if (_pressedSwitches == 0)
        return;
    else if (!HitTest(x, y))
    {
        if (_pressedSwitches != 0)
        {
            _pressedSwitches = 0;
            SimulateBits();
            MarkDirty();
            return;
        }
    }
        
    int width = D(WIDTH);
    int height = D(HEIGHT);
    int cx = _x + D(WIDTH) * 3 / 2;
    int cy = _y + D(HEIGHT) * 3 / 2;
    
    int dx = x - cx;
    int dy = y - cy;
    
    uint8_t newPressedSwitches = 0;
    
    if ((abs(dx) < width / 2) && (abs(dy) < height / 2))
        newPressedSwitches |= 1 << (uint8_t)ESwitchBitNumber::Button; // NOSONAR: ESP32 prefers uint8_t
    
    if (dy < -height / 2)
        newPressedSwitches |= 1 << (uint8_t)ESwitchBitNumber::Up; // NOSONAR: ESP32 prefers uint8_t
    else if (dy > D(HEIGHT) / 2)
        newPressedSwitches |= 1 << (uint8_t)ESwitchBitNumber::Down; // NOSONAR: ESP32 prefers uint8_t
    
    if (dx < -width / 2)
        newPressedSwitches |= 1 << (uint8_t)ESwitchBitNumber::Left; // NOSONAR: ESP32 prefers uint8_t
    else if (dx > width / 2)
        newPressedSwitches |= 1 << (uint8_t)ESwitchBitNumber::Right; // NOSONAR: ESP32 prefers uint8_t
    
    if (newPressedSwitches != _pressedSwitches)
    {
        _pressedSwitches = newPressedSwitches;
        SimulateBits();
        MarkDirty();
    }
}

void GdiAtariJoystick::OnMouseUp(int x, int y)
{
    if (_pressedSwitches != 0)
    {
        _pressedSwitches = 0;
        SimulateBits();
        MarkDirty();
    }
}

void GdiAtariJoystick::SimulateBits()
{
    uint16_t gpioStates = GetMcp23017DeviceDriver().GetMcp23017DeviceModel().GetGpioStates();
    gpioStates = BitUtilities::SetBit(
        gpioStates, _bitNumberUp,
        !(_pressedSwitches & (1 << (uint8_t) ESwitchBitNumber::Up)));
    gpioStates = BitUtilities::SetBit(
        gpioStates, _bitNumberRight,
        !(_pressedSwitches & (1 << (uint8_t)ESwitchBitNumber::Right)));
    gpioStates = BitUtilities::SetBit(
        gpioStates, _bitNumberDown,
        !(_pressedSwitches & (1 << (uint8_t)ESwitchBitNumber::Down)));
    gpioStates = BitUtilities::SetBit(
        gpioStates, _bitNumberLeft,
        !(_pressedSwitches & (1 << (uint8_t)ESwitchBitNumber::Left)));
    gpioStates = BitUtilities::SetBit(
        gpioStates, _bitNumberButton,
        !(_pressedSwitches & (1 << (uint8_t)ESwitchBitNumber::Button)));
    
    I2c& i2c = GetMcp23017DeviceDriver().GetI2cDeviceDriver().GetI2c();
    auto windowsI2c = dynamic_cast<WindowsI2c*>(&i2c);
    Assert::IsNotNullptr(windowsI2c, "WindowsI2c");

    windowsI2c->SetMcp23017IntCapReturn(gpioStates);
    Mcp23017DeviceDriver::SetInterruptTriggered();
}

void GdiAtariJoystick::Update(HDC* hdc)
{
    _hdc = hdc;
    POINT p;
    GetCursorPos(&p);
    ScreenToClient(_gdiScreen.GetHwnd(), &p);

    const int width = D(WIDTH);
    const int height = D(HEIGHT);

    // Draw surrounding circle.
    auto oldPen = (HPEN)SelectObject(*hdc, _surroundingPen);
    auto oldBrush = (HBRUSH)SelectObject(*hdc, _surroundingBrush);
    for (int line = 0; line < 4; line++)
    {
        // Draw horizontal lines.
        MoveToEx(*_hdc, _x, _y + height * line, nullptr);
        LineTo(*_hdc, _x + width * 3, _y + height * line);
        // Draw vertical lines.
        MoveToEx(*_hdc, _x + width * line, _y, nullptr);
        LineTo(*_hdc, _x + width * line, _y + height * 3);
    }

    SelectObject(*_hdc, oldPen);
    SelectObject(*_hdc, oldBrush);

    // Hover update.
    UpdateHover(p.x, p.y);

    bool pressedUp     = 
        BitUtilities::IsBitSet(_pressedSwitches, (uint8_t)ESwitchBitNumber::Up);
    bool pressedRight  = 
        BitUtilities::IsBitSet(_pressedSwitches, (uint8_t)ESwitchBitNumber::Right);
    bool pressedDown   = 
        BitUtilities::IsBitSet(_pressedSwitches, (uint8_t)ESwitchBitNumber::Down);
    bool pressedLeft   = 
        BitUtilities::IsBitSet(_pressedSwitches, (uint8_t)ESwitchBitNumber::Left);
    bool pressedButton = 
        BitUtilities::IsBitSet(_pressedSwitches, (uint8_t)ESwitchBitNumber::Button);

    std::array<POINT, 3> pointsUp = { {
        POINT{ _x + width * 3 / 2, _y}, // Upper point
        POINT{ _x + width * 2, _y + height }, // Right point, 
        POINT{ _x + width, _y + height } // Left point
    } };
    DrawTriangle(BrushFor(pressedUp, 
        BitUtilities::IsBitSet(_hoveredSwitches, (uint8_t)ESwitchBitNumber::Up)), 
        pointsUp.data());
   
    std::array<POINT, 3> pointsDown = { {
        POINT{ _x + width * 3 / 2, _y + height * 3}, // Lower point
        POINT{ _x + width * 2, _y + height * 2}, // Right point
        POINT{ _x + width, _y + height * 2} // Left point
    } };
    DrawTriangle(BrushFor(pressedDown, 
        BitUtilities::IsBitSet(_hoveredSwitches, (uint8_t)ESwitchBitNumber::Down)),
        pointsDown.data());
   
    std::array<POINT, 3> pointsLeft = { {
        POINT{ _x, _y + height * 3 / 2}, // Left point
        POINT{ _x + width, _y + height}, // Upper point
        POINT{ _x + width, _y + height * 2 } // Lower point
    } };
    DrawTriangle(BrushFor(pressedLeft, 
        BitUtilities::IsBitSet(_hoveredSwitches, (uint8_t)ESwitchBitNumber::Left)),
        pointsLeft.data());

    std::array<POINT, 3> pointsRight = { {
            POINT{ _x + width * 3, _y + height * 3 / 2}, // Right point
            POINT{ _x + width * 2, _y + height}, // Upper point
            POINT{ _x + width * 2, _y + height * 2 }, // Lower point
    } };
    DrawTriangle(BrushFor(pressedRight,
        BitUtilities::IsBitSet(_hoveredSwitches, (uint8_t)ESwitchBitNumber::Right)),
        pointsRight.data());

    bool isButtonHovered = BitUtilities::IsBitSet(
        _hoveredSwitches, (uint8_t)ESwitchBitNumber::Button);
    DrawCircle(BrushFor(pressedButton, isButtonHovered));
}

HBRUSH GdiAtariJoystick::BrushFor(bool pressed, bool hover)
{
    if (pressed) return _pressedBrush;
    if (hover)  return _hoverBrush;
    return _inactiveBrush;
}

void GdiAtariJoystick::DrawTriangle(HBRUSH brush, const POINT pts[3])
{
    auto oldBrush = (HBRUSH)SelectObject(*_hdc, brush);
    Polygon(*_hdc, pts, 3);
    SelectObject(*_hdc, oldBrush);
};

void GdiAtariJoystick::DrawCircle(
    HBRUSH brush)
{
    int width = D(WIDTH);
    int height = D(HEIGHT);

    auto oldBrush = (HBRUSH)SelectObject(*_hdc, brush);
    Ellipse(*_hdc, _x + width, _y + height, _x + width * 2, _y + height * 2);
    SelectObject(*_hdc, oldBrush);
}

void GdiAtariJoystick::UpdateHover(int mouseX, int mouseY)
{
    if (!HitTest(mouseX, mouseY))
    {
        _hoveredSwitches = 0;
        return;
    }
    int width = D(WIDTH);
    int height = D(HEIGHT);
    int cx = _x + width * 3 / 2;
    int cy = _y + height * 3 / 2;

    int dx = mouseX - cx;
    int dy = mouseY - cy;

    _hoveredSwitches = BitUtilities::SetBit(_hoveredSwitches, (uint8_t) ESwitchBitNumber::Button,
        (abs(dx) < width / 2) && (abs(dy) < height / 2));
    _hoveredSwitches = BitUtilities::SetBit(_hoveredSwitches, (uint8_t)ESwitchBitNumber::Up,
        (dy < -height / 2));
    _hoveredSwitches = BitUtilities::SetBit(_hoveredSwitches, (uint8_t)ESwitchBitNumber::Down,
        (dy > height / 2));
    _hoveredSwitches = BitUtilities::SetBit(_hoveredSwitches, (uint8_t)ESwitchBitNumber::Left,
        (dx < -width / 2));
    _hoveredSwitches = BitUtilities::SetBit(_hoveredSwitches, (uint8_t)ESwitchBitNumber::Right,
        (dx > width / 2));
}
