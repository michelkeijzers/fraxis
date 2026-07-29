#pragma once

#include <windows.h>

class IGdiMouseInput
{	
public:
	~IGdiMouseInput() = default;

	virtual bool HitTest(int, int y) = 0;
	virtual void OnMouseDown(int x, int y) = 0;
	virtual void OnMouseMove(int x, int y) = 0;
	virtual void OnMouseUp(int x, int y) = 0;

	virtual void Update(HDC* hdc) = 0;
};
