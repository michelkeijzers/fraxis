#include "Position.hpp"

Position::Position()
: 
    _xPosition(0), 
    _yPosition(0)
{
}

Position::Position(
    uint8_t xPosition, 
    uint8_t yPosition)
: 
    _xPosition(xPosition), 
    _yPosition(yPosition)
{
}

void Position::Set(
    uint8_t xPosition, 
    uint8_t yPosition)
{
    _xPosition = xPosition;
    _yPosition = yPosition;
}

void Position::SetX(
    uint8_t xPosition)
{
    _xPosition = xPosition;
}

void Position::SetY(
    uint8_t yPosition)
{
    _yPosition = yPosition;
}

void Position::Get(
    uint8_t& xPosition, 
    uint8_t& yPosition) const
{
    xPosition = _xPosition;
    yPosition = _yPosition;
}

uint8_t& Position::GetX()
{
    return _xPosition; 
}

uint8_t& Position::GetY()
{
    return _yPosition; 
}

const uint8_t& Position::GetX() const
{
    return _xPosition;
}

const uint8_t& Position::GetY() const
{
    return _yPosition;
}
