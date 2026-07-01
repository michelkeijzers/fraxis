#pragma once

#include <stdint.h>
#include <windows.h>
#include "../IGdiMouseInput.hpp"
#include "../../Core/Components/PinIo.hpp"

class WindowsMcp23017;
class GdiScreen;

class GdiAtariJoystick : public IGdiMouseInput
{
public:
	enum class EId
	{
		Player1 = 0,
		Player2 = 1
	};

	enum class EItem
	{
		Up =     1<<0,
		Down =   1<<1,
		Left =   1<<2,
		Right =  1<<3,
		Button = 1<<4
	};

	GdiAtariJoystick(EId joystickId, PinIo& pinIo, WindowsMcp23017& windowsMcp23017,
	 GdiScreen& gdiScreen, int x, int y);
	~GdiAtariJoystick();

	bool HitTest(int x, int y) override;
	void OnMouseDown(int x, int y) override;
	void OnMouseMove(int x, int y) override;
	void OnMouseUp(int x, int y) override;

	void Update(HDC* hdc);

	uint8_t GetPressedItems(); // Or-ed EItems

private:
	EId _joystickId;
	PinIo& _pinIo;
	WindowsMcp23017& _windowsMcp23017;
	GdiScreen& _gdiScreen;
	int _x;
	int _y;

	int D(int value) { return value * 2; } // Placeholder for scaling function

	uint8_t _pressedItems; // Bitmask for pressed items

	void UpdateMcp23017();
};
