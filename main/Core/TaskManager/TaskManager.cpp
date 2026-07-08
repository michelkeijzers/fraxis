#include "TaskManager.hpp"
#include "../Services/IRtosTask.hpp"
#include "../Services/IRtosQueue.hpp"
#include "../Components/LedStrips.hpp"
#include "../Components/Lcd1602Display.hpp"
#include "../Components/PinIo.hpp"
#include "../Components/Tm1637.hpp"
#include "../SharedUtils/Debug.hpp"

//TODO: Temp
uint32_t todo2500 = 100000;
uint32_t todo4800 = 0;
uint32_t todo2323 = 23 * 60 + 59;


TaskManager::TaskManager(Interfaces& interfaces)
: _interfaces(interfaces), _menuStates(), _menuRenderer(_menuStates), 
  _lastMenuUpdate(0), _lastLedStripsUpdate(0), _lastMcp23017Update(0), _lastLcd1602Update(0), _lastTm1637Update(0)
{
}

void TaskManager::Initialize()
{
    CreateTasks();
    CreateQueues();
    StartTasks();
    StartQueues();

    _interfaces.ledStrips.Initialize();
    _interfaces.lcdDisplay.Initialize();
    _interfaces.pinIo.Initialize();
	_interfaces.tm1637CentralPanel.Initialize();
	_interfaces.tm1637Player1.Initialize();
    _interfaces.tm1637Player2.Initialize();
}

void TaskManager::CreateTasks()
{

}

void TaskManager::CreateQueues()
{

}

void TaskManager::StartTasks()
{

}
void TaskManager::StartQueues()
{

}

void TaskManager::Run(bool keepRunning)
{
    if (keepRunning)
    {
        while (true)
        {
            RunOnce();
            _interfaces.rtosTask.DelayTask(1);
        }
    }
    else
    {
        RunOnce();
    }
}

void TaskManager::RunOnce()
{
    uint32_t now = _interfaces.rtosTask.GetTaskTickCount();

    TempSimulate();

    if (now - _lastMcp23017Update >= MCP23017_UPDATE_INTERVAL_MS)
    {
        _interfaces.pinIo.Update();
        _lastMcp23017Update = now;
    }

    if (now - _lastMenuUpdate >= MENU_UPDATE_INTERVAL_MS)
    {
        _menuStates.Update(_interfaces.pinIo.GetInputEvents());
        _interfaces.pinIo.GetInputEvents().clear();
        _lastMenuUpdate = now;
    }

    if (now - _lastLcd1602Update >= LCD_UPDATE_INTERVAL_MS)
    {
        MenuRenderer::Result result = _menuRenderer.Render();
        if (_menuRenderer.IsDirty())
        {
            _interfaces.lcdDisplay.WriteLines(result.line1.data(), result.line2.data());
            _interfaces.lcdDisplay.Update();
        }
        _lastLcd1602Update = now;
    }

    if (now - _lastTm1637Update >= TM1637_UPDATE_INTERVAL_MS)
    {
        _interfaces.tm1637CentralPanel.Update();
        _interfaces.tm1637Player1.Update();
        _interfaces.tm1637Player2.Update();
        _lastTm1637Update = now;
    }

    if (now - _lastLedStripsUpdate >= LED_STRIPS_UPDATE_INTERVAL_MS)
    {
        _interfaces.ledStrips.Update();
        _lastLedStripsUpdate = now;
    }
}

/// <summary>
/// Temporary function. TODO
/// </summary>
void TaskManager::TempSimulate()
{
    static uint8_t x = 0;
    x = (x + 10) % 72;
    static uint8_t y = 0;
    y = (y + 1) % 5;

    static uint32_t color = 0;
    color = (color + 5) % 255;

    for (int pixel = 0; pixel < 10; pixel++)
    {
        _interfaces.ledStrips.SetPixel((x + pixel) % 72, (y + pixel) % 5 ,
            (color + pixel * 10) % 256, (color + pixel * 10 + 50) % 256, (color + pixel * 10 + 100) % 256);
    }
    
    _interfaces.tm1637CentralPanel.SetTime(todo2323 / 60, todo2323 % 60);

    if (todo2500 % 40 == 0)
    {
        todo2323--;
    }

    _interfaces.tm1637Player1.SetValue(todo2500);
    todo2500 += 1;
    _interfaces.tm1637Player2.SetValue(todo4800);
    if (todo2500 % 10 == 0)
    {
        todo4800++;
    }

    _interfaces.pinIo.SetPauseLed(todo2500 % 100 < 50);
    _interfaces.pinIo.SetSelectLed(todo2500 % 100 > 30);
    _interfaces.pinIo.SetSetupLed(todo2500 % 100 > 20);
    _interfaces.pinIo.SetPlayer1Led(todo2500 % 5 > 3);
    _interfaces.pinIo.SetPlayer2Led(todo4800 % 10 == 0);

    // END TEMP
}
