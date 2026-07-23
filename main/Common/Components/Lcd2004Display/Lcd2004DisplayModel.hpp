#pragma once

#include "../ComponentModel.hpp"

class Lcd1602DisplayModel : public ComponentModel
{
public:
	Lcd1602DisplayModel();
	~Lcd1602DisplayModel() = default;

	void WriteLines(const char* line1, const char* line2);
	const char* GetLine1() const { return _line1; }	// NOT /0 terminated, for windows only
	const char* GetLine2() const { return _line2; }	// NOT /0 terminated, for windows only

protected:
	char _line1[16];
	char _line2[16];
};
