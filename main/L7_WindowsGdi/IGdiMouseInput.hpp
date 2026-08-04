#pragma once

#include <windows.h>
#include "../L9_Utilities/Dirty/Dirty.hpp"

class IGdiMouseInput : public Dirty
{	
public:
	~IGdiMouseInput() = default;

	virtual bool HitTest(
		int, 
		int y) = 0;
	virtual void OnMouseDown(
		int x,
		int y) = 0;
	virtual void OnMouseMove(
		int x,
		int y) = 0;
	virtual void OnMouseUp(
		int x, 
		int y) = 0;

	virtual void Update(
		HDC* hdc) = 0;
};
