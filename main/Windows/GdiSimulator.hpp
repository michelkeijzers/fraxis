#pragma once


//#include "Resource.h"
#include "../Windows/Components/WindowsRtos.hpp"
#include "../Windows/Components/WindowsRtosQueue.hpp"
#include "../Windows/Components/WindowsLedStrips.hpp"
#include "../Windows/Components/WindowsLcd1602Display.hpp"
#include "../Windows/Components/WindowsMcp23017.hpp"
#include "../Windows/Components/WindowsTm1637.hpp"
#include "../Windows/GdiScreen.hpp"
#include "../Core/Components/PinIo.hpp"
#include "../Core/Components/PinIoMappings.hpp"
#include "../Core/TaskManager/TaskManager.hpp"

WindowsRtos windowsRtos;
WindowsRtosQueue windowsRtosQueue(10, 10); //TODO

WindowsLedStrips windowsLedStrips;
WindowsLcd1602Display windowsLcd1602Display;
WindowsMcp23017 windowsMcp23017;
PinIo pinIo(windowsMcp23017);
WindowsTm1637 windowsTm1637CentralPanel(4);
WindowsTm1637 windowsTm1637Player1(6);
WindowsTm1637 windowsTm1637Player2(6);

TaskManager::Interfaces interfaces =
{
    windowsRtos, windowsRtosQueue, windowsLedStrips, windowsLcd1602Display, pinIo,
    windowsTm1637CentralPanel, windowsTm1637Player1, windowsTm1637Player2
};
TaskManager taskManager(interfaces);
GdiScreen gdiScreen(windowsLedStrips, interfaces.pinIo, windowsMcp23017, windowsLcd1602Display,
    windowsTm1637CentralPanel, windowsTm1637Player1, windowsTm1637Player2);
