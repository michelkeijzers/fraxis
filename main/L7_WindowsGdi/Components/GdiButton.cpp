#include "GdiButton.hpp"
#include "../../L5_DeviceModels/Mcp23017/Mcp23017DeviceModel.hpp"
#include "../../L6_DeviceDrivers/Mcp23017/Mcp23017DeviceDriver.hpp"
#include "../../L6_DeviceDrivers/I2c/I2cDeviceDriver.hpp"
#include "../../L8_Services/I2c/WindowsI2c.hpp"
#include "../../L9_Utilities/Log/Log.hpp"
#include "../../L9_Utilities/Assert/Assert.hpp"
#include "../../L9_Utilities/Math/BitUtilities.hpp"
#include "windows.h"

const int WIDTH = 20;
const int HEIGHT = 20;

GdiButton::GdiButton(
    std::string_view text,
    uint16_t bitNumber,
    int x,
    int y,
    Mcp23017DeviceDriver& mcp23017DeviceDriver)
    :
    _text(text),
    _bitNumber(bitNumber),
    _x(x),
    _y(y),
    _pressed(false),
    _hovered(false),
    _mcp23017DeviceDriver(mcp23017DeviceDriver)
{
    _font = CreateFont(
        -20,                // height (negative = character height)
        0,                  // width (0 = auto)
        0, 0,               // angle
        FW_BOLD,            // weight (FW_BOLD for bold)
        FALSE,              // italic
        FALSE,              // underline
        FALSE,              // strikeout
        DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_DONTCARE,
        L"Consolas"
    );

    _normalBrush = CreateSolidBrush(RGB(150, 50, 50));
    _hoverBrush = CreateSolidBrush(RGB(200, 50, 50));
    _pressedBrush = CreateSolidBrush(RGB(255, 50, 50));
    _borderPen = CreatePen(PS_SOLID, 2, RGB(40, 40, 40));
    MarkDirty(); // NOSONAR: Always refresh
}

GdiButton::~GdiButton()
{
    DeleteObject(_font);
    DeleteObject(_normalBrush);
    DeleteObject(_hoverBrush);
    DeleteObject(_pressedBrush);
    DeleteObject(_borderPen);
}

uint16_t GdiButton::D(
    uint16_t value) const
{
    return value * 2;
}

bool GdiButton::HitTest(int x, int y)
{
    return x >= _x && x <= _x + WIDTH &&
        y >= _y && y <= _y + HEIGHT;
}

void GdiButton::OnMouseDown(int x, int y)
{
    if (HitTest(x, y))
    {
        _pressed = true;
        _hovered = true;
        SimulateBit(true);
        MarkDirty();
    }
}

void GdiButton::OnMouseMove(int x, int y)
{
    _hovered = HitTest(x, y);
    if (_hovered)
    {
        _hovered = true;
        MarkDirty();
    }
    else if (_pressed)
    {
        _pressed = false;
        SimulateBit(false);
        MarkDirty();
    }
}

void GdiButton::OnMouseUp(int x, int y)
{
    if (_pressed)
    {
        _pressed = false;
        SimulateBit(false);
        MarkDirty();
    }
    MarkDirty();
}

void GdiButton::SimulateBit(
    bool on)
{
    uint16_t gpioStates = _mcp23017DeviceDriver.GetMcp23017DeviceModel().GetGpioStates();
    gpioStates = BitUtilities::SetBit(gpioStates, _bitNumber, !on); // Active low
    I2c& i2c = _mcp23017DeviceDriver.GetI2cDeviceDriver().GetI2c();
    auto windowsI2c = dynamic_cast<WindowsI2c*>(&i2c);
    Assert::IsNotNullptr(windowsI2c, "WindowsI2c");
    windowsI2c->SetMcp23017IntCapReturn(gpioStates);
    Mcp23017DeviceDriver::SetInterruptTriggered();
}

void GdiButton::Update(HDC * hdc)
{
    // Determine fill color
    HBRUSH brush = _pressedBrush;
    if (!_pressed)
    {
        brush = _hovered ? _hoverBrush : _normalBrush;
    }

    // Draw filled rectangle
    auto oldBrush = (HBRUSH)SelectObject(*hdc, brush);
    auto oldPen = (HPEN)SelectObject(*hdc, _borderPen);

    Rectangle(*hdc, _x, _y, _x + WIDTH, _y + HEIGHT);

    SelectObject(*hdc, oldBrush);
    SelectObject(*hdc, oldPen);

    // Draw centered text (optional)
    if (!_text.empty())
    {
        auto oldFont = (HFONT)SelectObject(*hdc, _font);
        SetBkMode(*hdc, TRANSPARENT);
        SetTextColor(*hdc, RGB(200, 10, 100));

        RECT r{ _x + WIDTH + 5, _y, _x + WIDTH + 70, _y + HEIGHT };
        DrawTextA(*hdc, _text.c_str(), -1, &r,
            DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        SelectObject(*hdc, oldFont);
    }
}
