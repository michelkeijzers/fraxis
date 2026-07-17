#include "WindowsComponentsBuilder.hpp"

#include "../../Common/Services/Rtos/WindowsRtos.hpp"
#include "../../Common/Services/RtosTask/WindowsRtosTask.hpp"
#include "../../Common/Services/RtosQueue/WindowsRtosQueue.hpp"
#include "../../Common/Services/Random/WindowsRandom.hpp"
#include "../../Common/Components/LedStrip/WindowsLedStripDriver.hpp"

#include "../../Core/Components/LedStrips.hpp"
#include "../../Common/Components/Lcd1602Display/WindowsLcd1602DisplayDriver.hpp"
#include "../../Common/Components/Tm1637/WindowsTm1637Driver.hpp"
#include "WindowsMcp23017.hpp"
#include "../../Core/Components/PinIo.hpp"
#include "../../Core/TaskManager/TaskManager.hpp"
#include "../../Common/Components/I2c/WindowsI2c.hpp"


WindowsComponentsBuilder::WindowsComponentsBuilder() : ComponentsBuilder()
{
}

void WindowsComponentsBuilder::BuildDrivers(Models& models)
{
    _drivers.rtos = new WindowsRtos();
    _drivers.random = new WindowsRandom();

    _drivers.ledStripDriver = new WindowsLedStripDriver();

    _drivers.i2c = new WindowsI2c();
    _drivers.lcd1602DisplayDriver = new WindowsLcd1602DisplayDriver(
        *(models.lcd1602DisplayModel), *(_drivers.i2c));
    _drivers.mcp23017 = new WindowsMcp23017();
    _drivers.tm1637CentralPanel = new WindowsTm1637Driver(*(models.tm1637ModelCentralPanel));
    _drivers.tm1637Player1 = new WindowsTm1637Driver(*(models.tm1637ModelPlayer1));
    _drivers.tm1637Player2 = new WindowsTm1637Driver(*(models.tm1637ModelPlayer2));
}
