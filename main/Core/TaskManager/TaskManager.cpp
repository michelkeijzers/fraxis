#include "TaskManager.hpp"
#include "../Services/IRtosTask.hpp"
#include "../Services/IRtosQueue.hpp"
#include "../Components/LedStrips.hpp"
#include "../Components/Lcd1602Display.hpp"
#include "../../Common/Components/LedStrip/LedStripDriver.hpp"
#include "../../Core/Components/Mcp23017.hpp"
#include "../Components/PinIo.hpp"
#include "../Components/Tm1637.hpp"
#include "../../Common/SharedUtils/Debug.hpp"

uint32_t simulatedPlayer1Score = 100000;
uint32_t simulatedPlayer2Score = 0;
uint32_t simulatedTime = 23 * 60 + 59;


TaskManager::TaskManager(ComponentsBuilder::FraxisComponents& fraxisComponents, ComponentsBuilder::Models& models, 
    ComponentsBuilder::Drivers& drivers)
: _fraxisComponents(fraxisComponents), _models(models), _drivers(drivers), _menuStates(), _menuRenderer(_menuStates), 
  _lastMenuUpdate(0), _lastLedStripsUpdate(0), _lastMcp23017Update(0), _lastLcd1602Update(0), _lastTm1637Update(0)
{
}

void TaskManager::Initialize()
{
    CreateTasks();
    CreateQueues();
    StartTasks();
    StartQueues();

    _fraxisComponents.pinIo->Initialize();

    _drivers.ledStripDriver->Initialize();
    
    //TODO to be done in various tasks
    _drivers.lcdDisplay->Initialize();
    // _drivers.rtosTask->Initialize(); TODO: Create (?) or make rtosTask Service
    //_drivers.i2c.Initialize();
    _drivers.mcp23017->Initialize();
    _drivers.tm1637CentralPanel->Initialize();
    _drivers.tm1637Player1->Initialize();
    _drivers.tm1637Player2->Initialize();
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
            _drivers.rtosTask->DelayTask(1);
        }
    }
    else
    {
        RunOnce();
    }
}

/// <summary>
/// TODO: To be done in various tasks
/// </summary>
void TaskManager::RunOnce()
{
    uint32_t now = _drivers.rtosTask->GetTaskTickCount();

    TempSimulate();

    if (now - _lastMcp23017Update >= MCP23017_UPDATE_INTERVAL_MS)
    {
        _fraxisComponents.pinIo->Update();
        _lastMcp23017Update = now;
    }

    if (now - _lastMenuUpdate >= MENU_UPDATE_INTERVAL_MS)
    {
        _menuStates.Update(_fraxisComponents.pinIo->GetInputEvents());
        _fraxisComponents.pinIo->GetInputEvents().clear();
        _lastMenuUpdate = now;
    }

    if (now - _lastLcd1602Update >= LCD_UPDATE_INTERVAL_MS)
    {
        MenuRenderer::Result result = _menuRenderer.Render();
        if (_menuRenderer.IsDirty())
        {
            _drivers.lcdDisplay->WriteLines(result.line1.data(), result.line2.data());
            //_drivers.lcdDisplay->Update();
        }
        _lastLcd1602Update = now;
    }

    if (now - _lastTm1637Update >= TM1637_UPDATE_INTERVAL_MS)
    {
        //TODO _interfaces.tm1637CentralPanel.Update(); ALSO WORKS WHEN NOT UPDATING (?)
        //TODO _interfaces.tm1637Player1.Update();
        //TODO _interfaces.tm1637Player2.Update();
        _lastTm1637Update = now;
    }

    // TODO: SHOULD BE DONE BY SYSTEM TASK
     if (now - _lastLedStripsUpdate >= LED_STRIPS_UPDATE_INTERVAL_MS)
     {
         _drivers.ledStripDriver->Send(_models.ledStripModel->GetBuffer(), LedStrips::NUMBER_OF_LEDS);
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
        _fraxisComponents.ledStrips->SetPixel((x + pixel) % 72, (y + pixel) % 5 ,
            (color + pixel * 10) % 256, (color + pixel * 10 + 50) % 256, (color + pixel * 10 + 100) % 256);
    }
    
    _drivers.tm1637CentralPanel->SetTime(simulatedTime / 60, simulatedTime % 60);

    if (simulatedPlayer1Score % 40 == 0)
    {
        simulatedTime--;
    }

    _drivers.tm1637Player1->SetValue(simulatedPlayer1Score);
    simulatedPlayer1Score++;
    _drivers.tm1637Player2->SetValue(simulatedPlayer2Score);
    if (simulatedPlayer1Score % 10 == 0)
    {
        simulatedPlayer2Score++;
    }

    PinIo& pinIo = *(_fraxisComponents.pinIo);
    pinIo.SetPauseLed(simulatedPlayer1Score % 100 < 50);
    pinIo.SetSelectLed(simulatedPlayer1Score % 100 > 30);
    pinIo.SetSetupLed(simulatedPlayer1Score % 100 > 20);
    pinIo.SetPlayer1Led(simulatedPlayer1Score % 5 > 3);
    pinIo.SetPlayer2Led(simulatedPlayer2Score % 10 == 0);

    // END TEMP
}
