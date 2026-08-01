#include "../../Application.hpp"
#include "../../../../L3_Messages/Types.hpp"

class AutoRun : public Application
{
public:
    AutoRun(Context& context, ApplicationsManager& applicationsManager);
    
    void Start() override;
    void Pause() override;
    void Resume() override;
    void Stop() override;
    void Run() override;

    void OnJoystickDirectionChanged(Types::EJoystickId id, Types::EJoystickDirection direction) override;
    void OnJoystickButtonChanged(Types::EJoystickId id, bool state) override;
    void OnSystemButtonChanged(bool state) override;
};


// @todo: Later: Implement auto runner 

//     static constexpr uint32_t MENU_UPDATE_INTERVAL_MS = 10;
//     static constexpr uint32_t LCD_UPDATE_INTERVAL_MS = 10;
//     static constexpr uint32_t MCP23017_UPDATE_INTERVAL_MS = 10;
//     static constexpr uint32_t TM1637_UPDATE_INTERVAL_MS = 100;

//     void TempSimulate(uint32_t now);


//     uint32_t _lastMcp23017Update;
//     uint32_t _lastLcd1602Update;
//     uint32_t _lastTm1637Update;


// void ApplicationsTask::TempSimulate(uint32_t now)
// {
//     static uint32_t previousTime = 0;
//     static uint8_t x = 0;
//     x = (x + 10) % 72;
//     static uint8_t y = 0;
//     y = (y + 1) % 5;

//     if (now - previousTime >= 1000)
//     {
//         simulatedPlayer2Score++;
//         previousTime = now;
//     }
    
//     //_models.tm1637DeviceModelCentralPanel->SetTime(simulatedTime / 60, simulatedTime % 60);
//     Message message;
//     message.id = Message::EId::Tm1637_Time;
//     message.tm1637_Time_Parameters.id = Message::ETm1637Id::CentralPanel;
//     message.tm1637_Time_Parameters.first = simulatedTime / 60;
//     message.tm1637_Time_Parameters.second = simulatedTime % 60;
//     _i2cQueue->Send(&message, 0);

//     if (simulatedPlayer1Score % 40 == 0)
//     {
//         simulatedTime--;
//     }

//     //_models.tm1637DeviceModelPlayer1->SetValue(simulatedPlayer1Score);
//     message.id = Message::EId::Tm1637_Value;
//     message.tm1637_Value_Parameters.id = Message::ETm1637Id::Player1;
//     message.tm1637_Value_Parameters.value = simulatedPlayer1Score;
//     _i2cQueue->Send(&message, 0);

//     //_models.tm1637DeviceModelPlayer2->SetValue(simulatedPlayer2Score);
//     message.id = Message::EId::Tm1637_Value;
//     message.tm1637_Value_Parameters.id = Message::ETm1637Id::Player2;
//     message.tm1637_Value_Parameters.value = simulatedPlayer2Score;
//     _i2cQueue->Send(&message, 0);

//     simulatedPlayer1Score += 7;

//     //PinIo& pinIo = *(_fraxisComponents.pinIo);
//     // pinIo.SetPauseLed(simulatedPlayer1Score % 600 < 50);
//     // pinIo.SetSelectLed(simulatedPlayer1Score % 300 > 250);
//     // pinIo.SetSetupLed(simulatedPlayer1Score % 1000 > 500);
//     // pinIo.SetPlayer1Led(simulatedPlayer1Score % 500 > 250);
//     // pinIo.SetPlayer2Led(simulatedPlayer2Score % 2 == 0);

//     if (simulatedPlayer1Score % 16 == 0)
//     {
//         //Random* random = _drivers.random;
//         //for (int ledStripX = 0; ledStripX < LedStrips::NUMBER_OF_LEDS_PER_LED_STRIP; ledStripX++)
//         {
//             //for (int ledStripY = 0; ledStripY < LedStrips::NUMBER_OF_LED_STRIPS; ledStripY++)
//             {
//                 //if (random->GetNext() % 500 == 0)
//                 {
//                     //Ws28xxDeviceModel::Pixel pixel = _fraxisComponents.ledStrips->GetPixel(ledStripX, ledStripY);
//                     //uint8_t red = MathUtilities::Clip(pixel.red + random->GetNext(10) - 5, 0, 255);
//                     // uint8_t green = MathUtilities::Clip(pixel.green + random->GetNext(10) - 5, 0, 255);
//                     // uint8_t blue = MathUtilities::Clip(pixel.blue + random->GetNext(10)  - 5, 0, 255);

//                     //_fraxisComponents.ledStrips->SetPixel(ledStripX, ledStripY, red, green, blue);
//                 }
//             }
//         }
//     }

//     // END TEMP
// }

