#include "TaskManager.hpp"
#include "../Services/IRtos.hpp"
#include "../Services/IRtosQueue.hpp"
#include "../Components/LedStrips.hpp"
#include "../Components/Lcd1602Display.hpp"
#include "../Components/PinIo.hpp"
#include "../Components/Tm1637.hpp"

//TODO: Temp
uint32_t todo2500 = 25;
uint32_t todo4800 = 0;
uint32_t todo2323 = 1000;


TaskManager::TaskManager(Interfaces& interfaces)
: _interfaces(interfaces), _menuInput(interfaces.pinIo), _menuStates(), _menuRenderer(_menuStates)
{
}

void TaskManager::Initialize()
{
    _interfaces.ledStrips.Initialize();
    _interfaces.lcdDisplay.Initialize();
    _interfaces.pinIo.Initialize();
	_interfaces.tm1637CentralPanel.Initialize();
	_interfaces.tm1637Player1.Initialize();
    _interfaces.tm1637Player2.Initialize();
}

void TaskManager::Run(bool keepRunning)
{
    if (keepRunning)
    {
        while (true)
        {
            RunOnce();
            _interfaces.rtos.DelayTask(1);
        }
    }
    else
    {
        RunOnce();
    }
}

void TaskManager::RunOnce()
{
    uint32_t now = _interfaces.rtos.GetTaskTickCount();

    TempSimulate();

    if (now - _lastMenuUpdate >= MENU_UPDATE_INTERVAL_MS)
    {
        EInput in = _menuInput.ReadInput();
        _menuStates.Update(in);
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

    if (now - _lastMcp23017Update >= MCP23017_UPDATE_INTERVAL_MS)
    {
        _interfaces.pinIo.Update();
        _lastMcp23017Update = now;
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
    static uint32_t index = 0;
    index = (index + 1) % 360;
    static uint32_t color = 0;
    color = (color + 5) % 255;

    _interfaces.ledStrips.SetPixel(index,
        color % 256,
        (color + 50) % 256,
        (color + 100) % 256);

    _interfaces.tm1637CentralPanel.SetTime(todo2323 / 60, todo2323 % 60);
    todo2323--;

    _interfaces.tm1637Player1.SetValue(todo2500);
    todo2500 += 97;
    _interfaces.tm1637Player2.SetValue(todo4800);
    todo4800 += 1;

    _interfaces.pinIo.SetPauseLed(todo4800 % 100 < 50);
    _interfaces.pinIo.SetSelectLed(todo4800 % 100 > 30);
    _interfaces.pinIo.SetSetupLed(todo4800 % 100 > 20);
    _interfaces.pinIo.SetPlayer1Led(todo4800 % 500 > 20);
    _interfaces.pinIo.SetPlayer2Led(todo4800 % 200 > 50);

    // END TEMP

}