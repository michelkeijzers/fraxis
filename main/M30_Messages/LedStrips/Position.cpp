#include "Position.hpp"

Position::Position()
: _x(0), _y(0)
{
}

Position::Position(
    uint8_t x, 
    uint8_t y)
: _x(x), _y(y)
{
}

Position::~Position()
{
}

void Position::Set(
    uint8_t x, 
    uint8_t y)
{
    _x = x;
    _y = y;
}

void Position::SetX(
    uint8_t x)
{
    x = x;
}

void Position::SetY(
    uint8_t y)
{
    _y = y;
}

void Position::Get(
    uint8_t& x, 
    uint8_t& y)
{
    x = _x;
    y = _y;
}

uint8_t& Position::GetX()
{
    return _x; 
}

uint8_t& Position::GetY()
{
    return _y; 
}

const uint8_t& Position::GetX() const
{
    return _x;
}

const uint8_t& Position::GetY() const
{
    return _y;
}

void Position::operator=(
    const Position& other)
{
    _x = other.GetX();
    _y = other.GetY();
}

bool Position::operator==(
    const Position& other) const
{
    return (_x == other.GetX()) && (_y == other.GetY());
}

bool Position::operator!=(
    const Position& other) const
{
    return !(*this == other);
}

void Position::operator+=(
    const Position& other)
{
    _x += other.GetX();
    _y += other.GetY();
}

void Position::operator-=(
    const Position& other)
{
    _x -= other.GetX();
    _y -= other.GetY();
}
