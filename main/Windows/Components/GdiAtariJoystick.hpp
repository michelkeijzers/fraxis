#pragma once

#include <stdint.h>
#include <windows.h>
#include "../IGdiMouseInput.hpp"
#include "../../Core/Components/PinIo.hpp"
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
		Up,
		Down,
		Left,
		Right,
		Button
	};

	GdiAtariJoystick(PinIo& pinIo, EId joystickId, GdiScreen& gdiScreen, int x, int y);
	~GdiAtariJoystick();

	bool HitTest(int x, int y) override;
	void OnMouseDown(int x, int y) override;
	void OnMouseMove(int x, int y) override;
	void OnMouseUp(int x, int y) override;

	void Update(HDC* hdc);

	uint8_t GetPressedItems(); // Or-ed EItems

private:
	PinIo& _pinIo;
	EId _joystickId;
	GdiScreen& _gdiScreen;
	int _x;
	int _y;

	int D(int value) { return value * 2; } // Placeholder for scaling function)

	//uint8_t _pressedItems; // Bitmask for pressed items
};

