#include "../L1_Composition/Context/Context.hpp"
#include "../L1_Composition/Context/DomainModelsContext.hpp"
#include "../L8_Services/Debug/Debug.hpp"
#include "../L8_Services/Random/Random.hpp"
#include "../L8_Services/Math/MathUtils.hpp"
#include "../L8_Services/RtosQueue/RtosQueue.hpp"

#include "ApplicationsTask.hpp"
// #include "../Core/Components/PinIo.hpp"
// #include "../Core/Components/LedStrips.hpp"
// #include "../Common/Components/Lcd1602Display/Lcd1602DisplayDriver.hpp"
// #include "../Common/Components/Lcd1602Display/Lcd1602DisplayModel.hpp"
// #include "../Common/Components/Tm1637/Tm1637Driver.hpp"
// #include "../Common/Components/Tm1637/Tm1637Model.hpp"
#include "../Tasks/Messages/Message.hpp" 
#include <cstring>

uint32_t simulatedPlayer1Score = 100000;
uint32_t simulatedPlayer2Score = 0;
uint32_t simulatedTime = 23 * 60 + 59;

ApplicationsTask::ApplicationsTask(Context& context) 
:   
    _context(context), _menuStates(), _menuRenderer(_menuStates),
    _lastMenuUpdate(0), _lastMcp23017Update(0), _lastLcd1602Update(0), _lastTm1637Update(0)
{
}

void ApplicationsTask::SetRtosTask(RtosTask* rtosTask)
{
    _rtosTask = rtosTask;
}

void ApplicationsTask::Run()
{
    while (true)
    {
        // system logic
        _rtosTask->DelayTask(1);

        uint32_t now = _rtosTask->GetTaskTickCount();

        TempSimulate(now);

        //if (_context.GetDomainModels().ledStripModel.IsDirty())
        {
            Message message;
            message.id = Message::EId::LedStrip_BufferReady;
            _ledStripQueue->Send(&message, 0);
        }

        MenuRenderer::Result result = _menuRenderer.Render();
        //_context.GetDomainModels().lcd2004Display.WriteLines(result.line1.data(), result.line2.data()); // TODO: Check dirty

        Message message;
        message.id = Message::EId::Lcd1602Display_TextLines;
        memcpy(message.lcd1602Display_TextLines_Parameters.line1, result.line1.data(), 16);
        memcpy(message.lcd1602Display_TextLines_Parameters.line2, result.line2.data(), 16);
            //_drivers.lcdDisplay->Update();
        _i2cQueue->Send(&message, 0);

        if (now - _lastMcp23017Update >= MCP23017_UPDATE_INTERVAL_MS)
        {
            //_fraxisComponents.pinIo->Update();
            _lastMcp23017Update = now;
        }

        if (now - _lastMenuUpdate >= MENU_UPDATE_INTERVAL_MS)
        {
            //_menuStates.Update(_fraxisComponents.pinIo->GetInputEvents());
            //_fraxisComponents.pinIo->GetInputEvents().clear();
            _lastMenuUpdate = now;
        }
    }
}


/// <summary>
/// Temporary function. TODO
/// </summary>
void ApplicationsTask::TempSimulate(uint32_t now)
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
    
    //_models.tm1637ModelCentralPanel->SetTime(simulatedTime / 60, simulatedTime % 60);
    Message message;
    message.id = Message::EId::Tm1637_Time;
    message.tm1637_Time_Parameters.id = Message::ETm1637Id::CentralPanel;
    message.tm1637_Time_Parameters.first = simulatedTime / 60;
    message.tm1637_Time_Parameters.second = simulatedTime % 60;
    _i2cQueue->Send(&message, 0);

    if (simulatedPlayer1Score % 40 == 0)
    {
        simulatedTime--;
    }

    //_models.tm1637ModelPlayer1->SetValue(simulatedPlayer1Score);
    message.id = Message::EId::Tm1637_Value;
    message.tm1637_Value_Parameters.id = Message::ETm1637Id::Player1;
    message.tm1637_Value_Parameters.value = simulatedPlayer1Score;
    _i2cQueue->Send(&message, 0);

    //_models.tm1637ModelPlayer2->SetValue(simulatedPlayer2Score);
    message.id = Message::EId::Tm1637_Value;
    message.tm1637_Value_Parameters.id = Message::ETm1637Id::Player2;
    message.tm1637_Value_Parameters.value = simulatedPlayer2Score;
    _i2cQueue->Send(&message, 0);

    simulatedPlayer1Score += 7;

    //PinIo& pinIo = *(_fraxisComponents.pinIo);
    // pinIo.SetPauseLed(simulatedPlayer1Score % 600 < 50);
    // pinIo.SetSelectLed(simulatedPlayer1Score % 300 > 250);
    // pinIo.SetSetupLed(simulatedPlayer1Score % 1000 > 500);
    // pinIo.SetPlayer1Led(simulatedPlayer1Score % 500 > 250);
    // pinIo.SetPlayer2Led(simulatedPlayer2Score % 2 == 0);

    if (simulatedPlayer1Score % 16 == 0)
    {
        //Random* random = _drivers.random;
        //for (int ledStripX = 0; ledStripX < LedStrips::NUMBER_OF_LEDS_PER_LED_STRIP; ledStripX++)
        {
            //for (int ledStripY = 0; ledStripY < LedStrips::NUMBER_OF_LED_STRIPS; ledStripY++)
            {
                //if (random->GetNext() % 500 == 0)
                {
                    //LedStripModel::Pixel pixel = _fraxisComponents.ledStrips->GetPixel(ledStripX, ledStripY);
                    //uint8_t red = MathUtils::Clip(pixel.red + random->GetNext(10) - 5, 0, 255);
                    // uint8_t green = MathUtils::Clip(pixel.green + random->GetNext(10) - 5, 0, 255);
                    // uint8_t blue = MathUtils::Clip(pixel.blue + random->GetNext(10)  - 5, 0, 255);

                    //_fraxisComponents.ledStrips->SetPixel(ledStripX, ledStripY, red, green, blue);
                }
            }
        }
    }

    // END TEMP
}
