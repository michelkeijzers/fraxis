#include "GdiAtariJoystick.hpp"
#include "../Components/WindowsMcp23017.hpp"
#include "../GdiScreen.hpp"
#include "../../Core/Components/PinIoMappings.hpp"

const int LENGTH = 90; // Entire joystick
const int WIDTH = 90;

GdiAtariJoystick::GdiAtariJoystick(EId joystickId, PinIo& pinIo,
    WindowsMcp23017& windowsMcp23017, GdiScreen& gdiScreen,
    int x, int y)
    : _joystickId(joystickId), _pinIo(pinIo),
    _windowsMcp23017(windowsMcp23017),
    _gdiScreen(gdiScreen), _x(x), _y(y),
    _pressedItems(0),
    _hoverUp(false), _hoverDown(false),
    _hoverLeft(false), _hoverRight(false),
    _hoverButton(false)
{}

GdiAtariJoystick::~GdiAtariJoystick()
{}

bool GdiAtariJoystick::HitTest(int x, int y)
{
    RECT r;
    r.left = _x;
    r.top = _y;
    r.right = _x + D(WIDTH);
    r.bottom = _y + D(LENGTH);

    return PtInRect(&r, POINT{ x, y });
}

void GdiAtariJoystick::OnMouseDown(int x, int y)
{
    if (!HitTest(x, y))
    {
        return;
    }

    uint8_t newMask = 0;

    int cx = _x + D(WIDTH / 2);
    int cy = _y + D(LENGTH / 2);

    int dx = x - cx;
    int dy = y - cy;

    // Button
    if (abs(dx) < D(10) && abs(dy) < D(10))
        newMask |= (int)EItem::Button;

    // Directions
    if ((dy >= D(-45)) && (dy < -D(15)))
        newMask |= (int)EItem::Up;
    else if ((dy > D(15)) && (dy < D(45)))
        newMask |= (int)EItem::Down;

    if ((dx >= -D(45)) && (dx < -D(15)))
        newMask |= (int)EItem::Left;
    else if ((dx > D(15)) && (dx < D(45)))
        newMask |= (int)EItem::Right;

    if (newMask != _pressedItems)
    {
        _pressedItems = newMask;
        UpdateMcp23017();
    }
}

void GdiAtariJoystick::OnMouseMove(int x, int y)
{
    // Update hover state ALWAYS
    UpdateHover(x, y);

    // Drag logic only when pressed
    if (_pressedItems == 0)
        return;
    
    int cx = _x + D(WIDTH / 2);
    int cy = _y + D(LENGTH / 2);

    int dx = x - cx;
    int dy = y - cy;

    uint8_t newMask = 0;

    if (abs(dx) < D(10) && abs(dy) < D(10))
        newMask |= (int)EItem::Button;

    if ((dy >= D(-45)) && (dy < -D(15)))
        newMask |= (int)EItem::Up;
    else if ((dy > D(15)) && (dy < D(45)))
        newMask |= (int)EItem::Down;

    if ((dx >= D(-45)) && (dx < -D(15)))
        newMask |= (int)EItem::Left;
    else if ((dx > D(15)) && (dx < D(45)))
        newMask |= (int)EItem::Right;

    if (newMask != _pressedItems)
    {
        _pressedItems = newMask;
        UpdateMcp23017();
    }
}

void GdiAtariJoystick::OnMouseUp(int x, int y)
{
    if (!HitTest(x, y))
    {
        return;
    }

    _pressedItems = 0;
    UpdateMcp23017();
}

void GdiAtariJoystick::UpdateHover(int mouseX, int mouseY)
{
    if (!HitTest(mouseX, mouseY))
    {
        _hoverUp = _hoverDown = _hoverLeft = _hoverRight = _hoverButton = false;
        return;
    }

    int cx = _x + D(WIDTH / 2);
    int cy = _y + D(LENGTH / 2);

    int dx = mouseX - cx;
    int dy = mouseY - cy;

    _hoverButton = (abs(dx) < D(10) && abs(dy) < D(10));

    _hoverUp = (dy < -D(15));
    _hoverDown = (dy > D(15));
    _hoverLeft = (dx < -D(15));
    _hoverRight = (dx > D(15));
}

void GdiAtariJoystick::Update(HDC* hdc)
{
    // Update hover every frame
    POINT p;
    GetCursorPos(&p);
    ScreenToClient(_gdiScreen.GetHwnd(), &p);
    UpdateHover(p.x, p.y);

    const int cellW = D(WIDTH) / 3;
    const int cellH = D(LENGTH) / 3;

    auto drawTriangle = [&](COLORREF color, const POINT pts[3])
        {
            HBRUSH brush = CreateSolidBrush(color);
            HPEN pen = CreatePen(PS_SOLID, 1, color);

            HBRUSH oldBrush = (HBRUSH)SelectObject(*hdc, brush);
            HPEN oldPen = (HPEN)SelectObject(*hdc, pen);

            Polygon(*hdc, pts, 3);

            SelectObject(*hdc, oldBrush);
            SelectObject(*hdc, oldPen);

            DeleteObject(brush);
            DeleteObject(pen);
        };

    auto drawCircle = [&](int cx, int cy, COLORREF color)
        {
            int x1 = _x + cx * cellW + cellW / 4;
            int y1 = _y + cy * cellH + cellH / 4;
            int x2 = _x + (cx + 1) * cellW - cellW / 4;
            int y2 = _y + (cy + 1) * cellH - cellH / 4;

            HBRUSH brush = CreateSolidBrush(color);
            HPEN pen = CreatePen(PS_SOLID, 1, color);

            HBRUSH oldBrush = (HBRUSH)SelectObject(*hdc, brush);
            HPEN oldPen = (HPEN)SelectObject(*hdc, pen);

            Ellipse(*hdc, x1, y1, x2, y2);

            SelectObject(*hdc, oldBrush);
            SelectObject(*hdc, oldPen);

            DeleteObject(brush);
            DeleteObject(pen);
        };

    auto colorFor = [&](bool active, bool hover)
        {
            if (active) return RGB(0, 200, 0);
            if (hover)  return RGB(0, 150, 0);
            return RGB(140, 140, 140);
        };

    bool up = (_pressedItems & (int)EItem::Up);
    bool down = (_pressedItems & (int)EItem::Down);
    bool left = (_pressedItems & (int)EItem::Left);
    bool right = (_pressedItems & (int)EItem::Right);
    bool button = (_pressedItems & (int)EItem::Button);

    POINT ptsUp[3] = {
        { _x + cellW * 1 + cellW / 2,     _y + cellH * 0 + cellH / 4 },
        { _x + cellW * 1 + cellW / 4,     _y + cellH * 0 + cellH * 3 / 4 },
        { _x + cellW * 1 + cellW * 3 / 4, _y + cellH * 0 + cellH * 3 / 4 }
    };
    drawTriangle(colorFor(up, _hoverUp), ptsUp);

    POINT ptsDown[3] = {
        { _x + cellW * 1 + cellW / 2,     _y + cellH * 2 + cellH * 3 / 4 },
        { _x + cellW * 1 + cellW / 4,     _y + cellH * 2 + cellH / 4 },
        { _x + cellW * 1 + cellW * 3 / 4, _y + cellH * 2 + cellH / 4 }
    };
    drawTriangle(colorFor(down, _hoverDown), ptsDown);

    POINT ptsLeft[3] = {
        { _x + cellW * 0 + cellW / 4,     _y + cellH * 1 + cellH / 2 },
        { _x + cellW * 0 + cellW * 3 / 4, _y + cellH * 1 + cellH / 4 },
        { _x + cellW * 0 + cellW * 3 / 4, _y + cellH * 1 + cellH * 3 / 4 }
    };
    drawTriangle(colorFor(left, _hoverLeft), ptsLeft);

    POINT ptsRight[3] = {
        { _x + cellW * 2 + cellW * 3 / 4, _y + cellH * 1 + cellH / 2 },
        { _x + cellW * 2 + cellW / 4,     _y + cellH * 1 + cellH / 4 },
        { _x + cellW * 2 + cellW / 4,     _y + cellH * 1 + cellH * 3 / 4 }
    };
    drawTriangle(colorFor(right, _hoverRight), ptsRight);

    drawCircle(1, 1, colorFor(button, _hoverButton));
}

void GdiAtariJoystick::UpdateMcp23017()
{
    if (_joystickId == EId::Player1)
    {
        _windowsMcp23017.SimulateSetGpioPin(PinIoMappings::EIdBit::Player1Up,
            (_pressedItems & (int)EItem::Up) ? 1 : 0);

        _windowsMcp23017.SimulateSetGpioPin(PinIoMappings::EIdBit::Player1Down,
            (_pressedItems & (int)EItem::Down) ? 1 : 0);

        _windowsMcp23017.SimulateSetGpioPin(PinIoMappings::EIdBit::Player1Left,
            (_pressedItems & (int)EItem::Left) ? 1 : 0);

        _windowsMcp23017.SimulateSetGpioPin(PinIoMappings::EIdBit::Player1Right,
            (_pressedItems & (int)EItem::Right) ? 1 : 0);

        _windowsMcp23017.SimulateSetGpioPin(PinIoMappings::EIdBit::Player1Button,
            (_pressedItems & (int)EItem::Button) ? 1 : 0);
    }
    else if (_joystickId == EId::Player2)
    {
        _windowsMcp23017.SimulateSetGpioPin(PinIoMappings::EIdBit::Player2Up,
            (_pressedItems & (int)EItem::Up) ? 1 : 0);

        _windowsMcp23017.SimulateSetGpioPin(PinIoMappings::EIdBit::Player2Down,
            (_pressedItems & (int)EItem::Down) ? 1 : 0);

        _windowsMcp23017.SimulateSetGpioPin(PinIoMappings::EIdBit::Player2Left,
            (_pressedItems & (int)EItem::Left) ? 1 : 0);

        _windowsMcp23017.SimulateSetGpioPin(PinIoMappings::EIdBit::Player2Right,
            (_pressedItems & (int)EItem::Right) ? 1 : 0);

        _windowsMcp23017.SimulateSetGpioPin(PinIoMappings::EIdBit::Player2Button,
            (_pressedItems & (int)EItem::Button) ? 1 : 0);
    }
}
