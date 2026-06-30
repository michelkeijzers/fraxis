#pragma once
#include <cstring> 
#include "../../Core/Components/Lcd1602Display.hpp"

class WindowsLcd1602Display : public Lcd1602Display
{
	void Initialize() override {}
	void Update() override;
	void WriteLines(const char* line1, const char* line2) override;

	const char* GetLine1() const; // Non terminated /0
	const char* GetLine2() const; // Non terminated /0
};