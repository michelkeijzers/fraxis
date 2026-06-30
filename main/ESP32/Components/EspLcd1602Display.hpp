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
	static constexpr uint8_t LCD_ADDR      = 0x27;    static constexpr uint8_t LCD_BACKLIGHT = 0x08;
    static constexpr uint8_t LCD_ENABLE    = 0x04;
    static constexpr uint8_t LCD_RS        = 0x01;

    void SetCursor(uint8_t col, uint8_t row);
    void Print(const char* s);

	EspI2c& _espI2c;
};


