#include "EspComponentsBuilder.hpp"
#include <cstdint>
#include <typeinfo>
#include "driver/i2c.h"
#include "driver/gpio.h"
#include "Common/Services/Rtos/EspRtos.hpp"
#include "Common/Services/RtosTask/EspRtosTask.hpp"
#include "Common/Services/Random/EspRandom.hpp"
#include "Common/Components/LedStrip/EspLedStripDriver.hpp"
#include "Core/Components/LedStrips.hpp"
#include "Common/Components/Lcd1602Display/EspLcd1602DisplayDriver.hpp"
#include "ESP32/Components/EspMcp23017.hpp"
#include "Common/Components/Tm1637/EspTm1637Driver.hpp"
#include "Common/Components/I2c/EspI2c.hpp"
#include "Core/Components/PinIo.hpp"
#include "Core/TaskManager/TaskManager.hpp"

EspComponentsBuilder::EspComponentsBuilder() : ComponentsBuilder()
{
}

void EspComponentsBuilder::BuildDrivers(Models& models)
{
    _drivers.rtos = new EspRtos();
    _drivers.random = new EspRandom();

    _drivers.i2c = new EspI2c(I2C_NUM_0, GPIO_NUM_16, GPIO_NUM_17, 100000);

    _drivers.ledStripDriver = new EspLedStripDriver(LedStrips::NUMBER_OF_LEDS, GPIO_NUM_18);
    _drivers.lcd1602DisplayDriver = new EspLcd1602DisplayDriver(*(models.lcd1602DisplayModel), *(_drivers.i2c));
    _drivers.mcp23017 = new EspMcp23017(static_cast<EspI2c&>(*(_drivers.i2c)));
    _drivers.tm1637CentralPanel = new EspTm1637Driver(*(models.tm1637ModelCentralPanel), GPIO_NUM_18, GPIO_NUM_13);
    _drivers.tm1637Player1 = new EspTm1637Driver(*(models.tm1637ModelPlayer1), GPIO_NUM_18, GPIO_NUM_14);
    _drivers.tm1637Player2 = new EspTm1637Driver(*(models.tm1637ModelPlayer2), GPIO_NUM_18, GPIO_NUM_27);
}
