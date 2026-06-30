#pragma once

#include <cstdint>

class AtariJoystick
{
public:
	enum class EId
	{
		Player1 = 0,
		Player2 = 1
	};

	enum class EItem
	{
		Up     = 1<<0,
		Down   = 1<<1,
		Left   = 1<<2,
		Right  = 1<<3,
		Button = 1<<4
	};

	AtariJoystick(EId joystickId);
	~AtariJoystick();

	
private:
	EId _joystickId;

	//uint8_t _pressedItems; // Bitmask for pressed items
};

