#include "WindowsLcd1602DisplayDriver.hpp"
#include <cstring>
#include <Windows.h>
#include "../../../Windows/GdiSimulator.hpp"

extern SimulatorContext _simulatorContext;

WindowsLcd1602DisplayDriver::WindowsLcd1602DisplayDriver(
    Lcd1602DisplayModel& model, I2c& i2c)
:   Lcd1602DisplayDriver(model, i2c)
{
}

void WindowsLcd1602DisplayDriver::Update()
{   
    PostMessage(_simulatorContext.hwndMain, WM_LCD_1602_DISPLAY_UPDATE, 0, 0);
}
