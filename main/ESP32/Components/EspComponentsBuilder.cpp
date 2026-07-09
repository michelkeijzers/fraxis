#include "EspComponentsBuilder.hpp"

#include "driver/i2c.h"
#include "driver/gpio.h"
#include "ESP32/Services/EspRtosTask.hpp"
#include "ESP32/Services/EspRtosQueue.hpp"
#include "ESP32/Services/EspTimer.hpp"
#include "Common/Components/LedStrip/EspLedStripDriver.hpp"
#include "Core/Components/LedStrips.hpp"
#include "ESP32/Components/EspLcd1602Display.hpp"
#include "ESP32/Components/EspMcp23017.hpp"
#include "ESP32/Components/EspTm1637.hpp"
#include "ESP32/EspI2c.hpp"
#include "Core/Components/PinIo.hpp"
#include "Core/TaskManager/TaskManager.hpp"


EspComponentsBuilder::EspComponentsBuilder() : ComponentsBuilder()
{
}

void EspComponentsBuilder::BuildDrivers()
{
    _drivers.rtosTask = new EspRtosTask();
    //
    _drivers.ledStripDriver = new EspLedStripDriver(LedStrips::NUMBER_OF_LEDS, GPIO_NUM_18);
    _espI2c = new EspI2c(I2C_NUM_0, GPIO_NUM_16, GPIO_NUM_17, 100000);
    _drivers.mcp23017 = new EspMcp23017(*_espI2c);
    _drivers.tm1637CentralPanel = new EspTm1637(4, GPIO_NUM_18, GPIO_NUM_13);
    _drivers.tm1637Player1 = new EspTm1637(6, GPIO_NUM_18, GPIO_NUM_14);
    _drivers.tm1637Player2 = new EspTm1637(6, GPIO_NUM_18, GPIO_NUM_27);
}
