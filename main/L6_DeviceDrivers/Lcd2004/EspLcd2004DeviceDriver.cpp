#include "EspLcd2004DeviceDriver.hpp"
#include "../I2c/I2cDeviceDriver.hpp"
#include "../../L5_DeviceModels/Lcd2004/Lcd2004Model.hpp"
#include "../../L9_Utils/Assert/Assert.hpp"
#include "driver/i2c.h"
#include <cstdint>

EspLcd2004DeviceDriver::EspLcd2004DeviceDriver()
{
}

EspLcd2004DeviceDriver::~EspLcd2004DeviceDriver()
{
}

void EspLcd2004DeviceDriver::Initialize()
{
    // TODO: Improve: do not call vTaskDelay but get via context
	vTaskDelay(pdMS_TO_TICKS(50));

	// 4‑bit init sequence
	WriteNibble(0x30, 0);
	vTaskDelay(pdMS_TO_TICKS(5));
	WriteNibble(0x30, 0);
	vTaskDelay(pdMS_TO_TICKS(1));
	WriteNibble(0x20, 0);

	Command(0x28); // 4‑bit, 4 lines
	Command(0x0C); // display on
	Command(0x06); // entry mode
	Command(0x01); // clear
	vTaskDelay(pdMS_TO_TICKS(2));  
}

void EspLcd2004DeviceDriver::PrintChar(char c)
{
    Data(c);
}

void EspLcd2004DeviceDriver::PrintLine(std::string line)
{
    for (uint8_t index = 0; index < line.length(); index++)
	{
        PrintChar(line[index]);
	}
}

void EspLcd2004DeviceDriver::SetCursor(uint8_t row, uint8_t column) 
{
    static constexpr uint8_t row_offsets[] = {0x00, 0x40, 0x14, 0x54}; // LCD2004
    Command(0x80 | (row_offsets[row] + column));
}

void EspLcd2004DeviceDriver::Command(uint8_t cmd)
{
    WriteByte(cmd, 0);
}

void EspLcd2004DeviceDriver::Data(uint8_t d)
{
    WriteByte(d, 1);
}

void EspLcd2004DeviceDriver::WriteNibble(uint8_t nibble, uint8_t rs)
{
    uint8_t data = nibble | LCD_BACKLIGHT | (rs ? LCD_RS : 0);

    uint8_t buf[3] = {
        data,
        static_cast<uint8_t>(data | LCD_ENABLE),
        data
    };

    auto* lcd2004Model = static_cast<Lcd2004Model*>(&GetDeviceModel());
    Assert::IsNotNullptr(lcd2004Model, "lcd2004Model");
    uint8_t i2cAddress = lcd2004Model->GetI2cAddress();
    _i2cDeviceDriver->Write(i2cAddress, buf, sizeof(buf));
}

void EspLcd2004DeviceDriver::WriteByte(uint8_t byte, uint8_t rs)
{
    WriteNibble(byte & 0xF0, rs);
    WriteNibble((byte << 4) & 0xF0, rs);
}

