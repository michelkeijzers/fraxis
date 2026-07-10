#include "SystemTask.hpp"
#include "../../Core/Components/PinIo.hpp"
#include "../../Core/Components/ComponentsBuilder.hpp"
#include "../../Core/Components/LedStrips.hpp"
#include "../../Core/Components/Lcd1602Display.hpp"
#include "../../Core/Components/Tm1637.hpp"
#include "../../Common/Services/Debug/Debug.hpp"

uint32_t simulatedPlayer1Score = 100000;
uint32_t simulatedPlayer2Score = 0;
uint32_t simulatedTime = 23 * 60 + 59;

SystemTask::SystemTask(RtosTask* rtosTask, 
    ComponentsBuilder::FraxisComponents& fraxisComponents, ComponentsBuilder::Drivers& drivers)
: _rtosTask(rtosTask), _fraxisComponents(fraxisComponents), _drivers(drivers),
    _menuStates(), _menuRenderer(_menuStates),
    _lastMenuUpdate(0), _lastMcp23017Update(0), _lastLcd1602Update(0), _lastTm1637Update(0)
{
}

void SystemTask::SetRtosTask(RtosTask* rtosTask)
{
    _rtosTask = rtosTask;
}

void SystemTask::Run()
{
    while (true)
    {
        // system logic
        _rtosTask->DelayTask(1);

        uint32_t now = _rtosTask->GetTaskTickCount();
        Debug::PrintInt("Now", now);
        Debug::PrintNewLine();

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
    }
}


/// <summary>
/// Temporary function. TODO
/// </summary>
void SystemTask::TempSimulate()
{
    static uint8_t x = 0;
    x = (x + 10) % 72;
    static uint8_t y = 0;
    y = (y + 1) % 5;

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
