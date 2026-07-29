#include <windows.h>

#include "../IGdiMouseInput.hpp"
#include "../../Core/Components/PinIoMappings.hpp"
#include <cstdint>

class WindowsMcp23017;
class GdiScreen;

class GdiButton : public IGdiMouseInput
{
private:
	RECT r;
	bool pressed = false;
	bool hovered = false;

	WindowsMcp23017& _windowsMcp23017;
	GdiScreen& _gdiScreen;

    PinIoMappings::EIdBit _idBit;

public:
	GdiButton(WindowsMcp23017& windowsMcp23017, PinIoMappings::EIdBit idBit,
        GdiScreen& gdiScreen, int x, int y, int w, int h);
	
	bool HitTest(int x, int y) override;
	void OnMouseDown(int x, int y) override;
	void OnMouseMove(int x, int y) override;
	void OnMouseUp(int x, int y) override;

	void Update(HDC* hdc);
};
