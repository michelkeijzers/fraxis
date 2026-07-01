#pragma once

#include <cstdint>

class PinIo;

enum class EInput 
{
    NONE, 
    SYSTEM_BUTTON,
    P1_UP,
    P1_DOWN, 
    P1_LEFT,
    P1_RIGHT,
    P1_BUTTON,
    P2_BUTTON,
    P2_UP,
    P2_DOWN,
    P2_LEFT,
    P2_RIGHT
};

class MenuInput 
{
public:
	MenuInput(PinIo& pinIo);
	~MenuInput();

   EInput ReadInput();

private:
    PinIo& _pinIo;
};
