#include "WindowsComponentsBuilder.hpp"

#include "../../Common/Services/WindowsRtosTask.hpp"
#include "../../Common/Services/WindowsRtosQueue.hpp"
#include "../../Common/Components/LedStrip/WindowsLedStripDriver.hpp"

#include "../../Core/Components/LedStrips.hpp"
#include "WindowsLcd1602Display.hpp"
#include "WindowsMcp23017.hpp"
#include "WindowsTm1637.hpp"
#include "../../Core/Components/PinIo.hpp"
#include "../../Core/TaskManager/TaskManager.hpp"


WindowsComponentsBuilder::WindowsComponentsBuilder() : ComponentsBuilder()
{
}

void WindowsComponentsBuilder::BuildDrivers()
{
    _drivers.rtosTask = new WindowsRtosTask();
    //
    _drivers.ledStripDriver = new WindowsLedStripDriver();
    _drivers.lcdDisplay = new WindowsLcd1602Display();
    _drivers.mcp23017 = new WindowsMcp23017();
    _drivers.tm1637CentralPanel = new WindowsTm1637(4);
    _drivers.tm1637Player1 = new WindowsTm1637(6);
    _drivers.tm1637Player2 = new WindowsTm1637(6);
}
