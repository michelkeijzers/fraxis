#pragma once

#include "Lcd1602DisplayDriver.hpp"
#include <cstring> 

class Lcd1602DisplayModel;
class I2c;

class WindowsLcd1602DisplayDriver : public Lcd1602DisplayDriver
{
public:
    WindowsLcd1602DisplayDriver(Lcd1602DisplayModel& model, I2c& i2c);

	void Initialize() override {}

    void Update() override;
};