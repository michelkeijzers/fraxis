#pragma once

#include "../../Core/Components/Lcd1602Display.hpp"
#include <cstdint>


class EspI2c;

class EspLcd1602Display : public Lcd1602Display
{
public:
	EspLcd1602Display(EspI2c& i2c);
	~EspLcd1602Display();

	void Initialize() override;
	void Update() override;
	void WriteLines(const char* line1, const char* line2) override;

	void Command(uint8_t cmd);
	void Data(uint8_t d);

	void WriteNibble(uint8_t nibble, uint8_t rs);
	void WriteByte(uint8_t byte, uint8_t rs);

private:
    void SetCursor(uint8_t col, uint8_t row);
    void Print(const char* s);

	EspI2c& _espI2c;
};


