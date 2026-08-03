#include "Color.hpp"

Color::Color()
:   _red(0),
    _green(0), 
    _blue(0)
{
}

Color::Color(
    uint8_t red, 
    uint8_t green, 
    uint8_t blue)
:   _red(red), 
    _green(green), 
    _blue(blue)
{
}

Color::~Color()
{
}

void Color::Set(
    uint8_t red, 
    uint8_t green, 
    uint8_t blue)
{
    _red   = red;
    _green = green;
    _blue  = blue;
}

void Color::SetRed(
    uint8_t red)
{
    _red = red;
}

void Color::SetGreen(
    uint8_t green)
{
    _green = green;
}

void Color::SetBlue(
    uint8_t blue)
{
    _blue = blue;
}

void Color::Get(
    uint8_t& red, 
    uint8_t& green, 
    uint8_t& blue)
{
    red   = _red;
    green = _green;
    blue  = _blue;
}

uint8_t Color::GetRed() const 
{
    return _red; 
}

uint8_t Color::GetGreen() const 
{
    return _green; 
}

uint8_t Color::GetBlue() const 
{
    return _blue; 
}

uint16_t Color::GetSum() const
{
    return _red + _green + _blue;
}

void Color::operator=(
    const Color& other)
{
    _red   = other._red;
    _green = other._green;
    _blue  = other._blue;
}

bool Color::operator==(
    const Color& other) const
{
    return (_red == other._red) && (_green == other._green) && (_blue == other._blue);
}

bool Color::operator!=(
    const Color& other) const
{
    return !(*this == other);
}

void Color::operator+=(
    const Color& other)
{
    _red   += other.GetRed();
    _green += other.GetGreen();
    _blue  += other.GetBlue();
}

void Color::operator-=(
    const Color& other)
{
    _red   -= other.GetRed();
    _green -= other.GetGreen();
    _blue  -= other.GetBlue();
}

void Color::AdjustBrightness(
    uint8_t brightness)
{
    _red   = (_red   * brightness) / 255;
    _green = (_green * brightness) / 255;
    _blue  = (_blue  * brightness) / 255;
}
