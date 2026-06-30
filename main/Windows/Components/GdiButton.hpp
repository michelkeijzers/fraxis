#include <windows.h>

#include "../IGdiMouseInput.hpp"

class GdiScreen;

class GdiButton : public IGdiMouseInput
{
private:
	RECT r;
	bool pressed = false;
	bool hovered = false;

	GdiScreen& _gdiScreen;

public:
	GdiButton(GdiScreen& gdiScreen, int x, int y, int w, int h);
	
	bool HitTest(int x, int y) override;
	void OnMouseDown(int x, int y) override;
	void OnMouseMove(int x, int y) override;
	void OnMouseUp(int x, int y) override;

	void Update(HDC* hdc);
};
