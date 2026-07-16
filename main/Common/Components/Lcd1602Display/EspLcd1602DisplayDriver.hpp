#pragma once

#include "Lcd1602DisplayDriver.hpp"
#include <cstdint>

class Lcd1602DisplayModel;
class I2c;

class EspLcd1602DisplayDriver : public Lcd1602DisplayDriver
{
public:
	EspLcd1602DisplayDriver(Lcd1602DisplayModel& model, I2c& i2c);
	
	void Initialize() override;
	void Update();

	void Command(uint8_t cmd);
	void Data(uint8_t d);

	void WriteNibble(uint8_t nibble, uint8_t rs);
	void WriteByte(uint8_t byte, uint8_t rs);

private:
    void SetCursor(uint8_t col, uint8_t row);
    void Print(const char* s);
};


