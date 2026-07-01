#pragma once

#include "IComponent.hpp"

class Lcd1602Display : public IComponent
{
public:
	Lcd1602Display();
	~Lcd1602Display() = default;

	virtual void WriteLines(const char* line1, const char* line2) = 0;

	const char* GetLine1() const { return _line1; }	// NOT /0 terminated, for windows only
	const char* GetLine2() const { return _line2; }	// NOT /0 terminated, for windows only

protected:
	char _line1[16];
	char _line2[16];
};

