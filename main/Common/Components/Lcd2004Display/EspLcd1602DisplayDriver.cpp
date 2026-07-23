#include "EspLcd1602DisplayDriver.hpp"
#include "Lcd1602DisplayModel.hpp"
#include "../I2c/EspI2c.hpp"
#include <string.h>

static constexpr uint8_t LCD_ADDR      = 0x27;
static constexpr uint8_t LCD_BACKLIGHT = 0x08;
static constexpr uint8_t LCD_ENABLE    = 0x04;
static constexpr uint8_t LCD_RS        = 0x01;

EspLcd1602DisplayDriver::EspLcd1602DisplayDriver(Lcd1602DisplayModel& model, I2c& i2c)
: Lcd1602DisplayDriver(model, i2c)
{
}

void EspLcd1602DisplayDriver::Initialize()
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

void EspLcd1602DisplayDriver::Update() 
{
    if (_model.IsDirty())
    {
        SetCursor(0, 0);
        Print(_model.GetLine1());

        SetCursor(0, 1);
        Print(_model.GetLine2());
    }
}

void EspLcd1602DisplayDriver::Command(uint8_t cmd)
{
    WriteByte(cmd, 0);
}

void EspLcd1602DisplayDriver::Data(uint8_t d)
{
    WriteByte(d, 1);
}

void EspLcd1602DisplayDriver::WriteNibble(uint8_t nibble, uint8_t rs)
{
    uint8_t data = nibble | LCD_BACKLIGHT | (rs ? LCD_RS : 0);

    uint8_t buf[3] = {
        data,
        static_cast<uint8_t>(data | LCD_ENABLE),
        data
    };

    _i2c.Write(LCD_ADDR, buf, sizeof(buf));
}

void EspLcd1602DisplayDriver::WriteByte(uint8_t byte, uint8_t rs)
{
    WriteNibble(byte & 0xF0, rs);
    WriteNibble((byte << 4) & 0xF0, rs);
}


void EspLcd1602DisplayDriver::SetCursor(uint8_t col, uint8_t row)
{
    static constexpr uint8_t row_offsets[] = {0x00, 0x40};
    Command(0x80 | (col + row_offsets[row]));
}

void EspLcd1602DisplayDriver::Print(const char* s)
{
    while (*s)
	{
        Data(*s++);
	}
}

