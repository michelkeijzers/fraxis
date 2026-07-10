#include "EspLcd1602Display.hpp"
#include "../EspI2c.hpp"
#include <string.h>

static constexpr uint8_t LCD_ADDR      = 0x27;
static constexpr uint8_t LCD_BACKLIGHT = 0x08;
static constexpr uint8_t LCD_ENABLE    = 0x04;
static constexpr uint8_t LCD_RS        = 0x01;

EspLcd1602Display::EspLcd1602Display(EspI2c &espI2c)
: _espI2c(espI2c)
{
}

void EspLcd1602Display::Initialize()
{
	vTaskDelay(pdMS_TO_TICKS(50));

	// 4‑bit init sequence
	WriteNibble(0x30, 0);
	vTaskDelay(pdMS_TO_TICKS(5));
	WriteNibble(0x30, 0);
	vTaskDelay(pdMS_TO_TICKS(1));
	WriteNibble(0x20, 0);

	Command(0x28); // 4‑bit, 2 lines
	Command(0x0C); // display on
	Command(0x06); // entry mode
	Command(0x01); // clear
	vTaskDelay(pdMS_TO_TICKS(2));  
}

void EspLcd1602Display::Update() 
{
        SetCursor(0, 0);
        Print(_line1);

        SetCursor(0, 1);
        Print(_line2);
}

void EspLcd1602Display::WriteLines(const char* line1, const char* line2)
{
	memcpy(_line1, line1, 16);
	memcpy(_line2, line2, 16);
}

void EspLcd1602Display::Command(uint8_t cmd)
{
    WriteByte(cmd, 0);
}

void EspLcd1602Display::Data(uint8_t d)
{
    WriteByte(d, 1);
}

void EspLcd1602Display::WriteNibble(uint8_t nibble, uint8_t rs)
{
    uint8_t data = nibble | LCD_BACKLIGHT | (rs ? LCD_RS : 0);

    uint8_t buf[3] = {
        data,
        static_cast<uint8_t>(data | LCD_ENABLE),
        data
    };

    _espI2c.Write(LCD_ADDR, buf, sizeof(buf));
}

void EspLcd1602Display::WriteByte(uint8_t byte, uint8_t rs)
{
    WriteNibble(byte & 0xF0, rs);
    WriteNibble((byte << 4) & 0xF0, rs);
}


void EspLcd1602Display::SetCursor(uint8_t col, uint8_t row)
{
    static constexpr uint8_t row_offsets[] = {0x00, 0x40};
    Command(0x80 | (col + row_offsets[row]));
}

void EspLcd1602Display::Print(const char* s)
{
    while (*s)
	{
        Data(*s++);
	}
}

