#include "SystemTask.hpp"
#include "../../Core/Components/PinIo.hpp"
#include "../../Core/Components/ComponentsBuilder.hpp"
#include "../../Core/Components/LedStrips.hpp"
#include "../../Common/Components/Lcd1602Display/Lcd1602DisplayDriver.hpp"
#include "../../Common/Components/Lcd1602Display/Lcd1602DisplayModel.hpp"
#include "../../Core/Components/Tm1637.hpp"
#include "../../Common/Services/Debug/Debug.hpp"
#include "../../Common/Services/Random/Random.hpp"
#include "../../Common/Services/Math/MathUtils.hpp"
#include "../Messages/Message.hpp" 
#include "../../Common/Services/RtosQueue/RtosQueue.hpp"
#include <cstring>

uint32_t simulatedPlayer1Score = 100000;
uint32_t simulatedPlayer2Score = 0;
uint32_t simulatedTime = 23 * 60 + 59;

SystemTask::SystemTask(RtosTask* rtosTask, RtosQueue* ledStripQueue, RtosQueue* i2cQueue,
    ComponentsBuilder::FraxisComponents& fraxisComponents, 
    ComponentsBuilder::Models& models,
    ComponentsBuilder::Drivers& drivers)
:   _rtosTask(rtosTask), _ledStripQueue(ledStripQueue), _i2cQueue(i2cQueue),
    _fraxisComponents(fraxisComponents), _models(models), _drivers(drivers),
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

        TempSimulate(now);

        if (_models.ledStripModel->IsDirty())
        {
            Message message;
            message.id = Message::EId::LedStrip_BufferReady;
            _ledStripQueue->Send(&message, 0);
        }

        MenuRenderer::Result result = _menuRenderer.Render();
        _models.lcd1602DisplayModel->WriteLines(result.line1.data(), result.line2.data()); // TODO: Check dirty

        if (_models.lcd1602DisplayModel->IsDirty())
        {
            Message message;
            message.id = Message::EId::Lcd1602Display_TextLines;
            memcpy(message.lcd1602Display_TextLines_Parameters.line1, result.line1.data(), 16);
            memcpy(message.lcd1602Display_TextLines_Parameters.line2, result.line2.data(), 16);
                //_drivers.lcdDisplay->Update();
            _i2cQueue->Send(&message, 0);
        }

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
void SystemTask::TempSimulate(uint32_t now)
{
    static uint32_t previousTime = 0;
    static uint8_t x = 0;
    x = (x + 10) % 72;
    static uint8_t y = 0;
    y = (y + 1) % 5;

    if (now - previousTime >= 1000)
    {
        simulatedPlayer2Score++;
        previousTime = now;
    }
    _drivers.tm1637CentralPanel->SetTime(simulatedTime / 60, simulatedTime % 60);

    if (simulatedPlayer1Score % 40 == 0)
    {
        simulatedTime--;
    }

    _drivers.tm1637Player1->SetValue(simulatedPlayer1Score);
  
    _drivers.tm1637Player2->SetValue(simulatedPlayer2Score);
    simulatedPlayer1Score += 7;

    PinIo& pinIo = *(_fraxisComponents.pinIo);
    pinIo.SetPauseLed(simulatedPlayer1Score % 600 < 50);
    pinIo.SetSelectLed(simulatedPlayer1Score % 300 > 250);
    pinIo.SetSetupLed(simulatedPlayer1Score % 1000 > 500);
    pinIo.SetPlayer1Led(simulatedPlayer1Score % 500 > 250);
    pinIo.SetPlayer2Led(simulatedPlayer2Score % 2 == 0);

    if (simulatedPlayer1Score % 16 == 0)
    {
        Random* random = _drivers.random;
        for (int ledStripX = 0; ledStripX < LedStrips::NUMBER_OF_LEDS_PER_LED_STRIP; ledStripX++)
        {
            for (int ledStripY = 0; ledStripY < LedStrips::NUMBER_OF_LED_STRIPS; ledStripY++)
            {
                if (random->GetNext() % 1000 == 0)
                {
                    LedStripModel::Pixel pixel = _fraxisComponents.ledStrips->GetPixel(ledStripX, ledStripY);
                    uint8_t red = MathUtils::Clip(pixel.red + random->GetNext(10) - 5, 0, 255);
                    uint8_t green = MathUtils::Clip(pixel.green + random->GetNext(10) - 5, 0, 255);
                    uint8_t blue = MathUtils::Clip(pixel.blue + random->GetNext(10)  - 5, 0, 255);

                    _fraxisComponents.ledStrips->SetPixel(ledStripX, ledStripY, red, green, blue);
                }
            }
        }
    }

    // END TEMP
}
