#pragma once

#include "Lcd2004DeviceDriver.hpp"
#include <cstdint>
#include <string>

class EspLcd2004DeviceDriver : public Lcd2004DeviceDriver
{
public:
    EspLcd2004DeviceDriver();
    ~EspLcd2004DeviceDriver();

    void Initialize() override;

protected:
    void PrintChar(char c) override;
    void PrintLine(std::string_view line) override;
    void SetCursor(uint8_t row, uint8_t column) override;

private:
	void Command(uint8_t cmd);
	void Data(uint8_t d);

	void WriteNibble(uint8_t nibble, uint8_t rs);
	void WriteByte(uint8_t byte, uint8_t rs);
    
    static constexpr uint8_t LCD_BACKLIGHT = 0x08;
    static constexpr uint8_t LCD_ENABLE    = 0x04;
    static constexpr uint8_t LCD_RS        = 0x01;
};
