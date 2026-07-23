
#include "I2cTask.hpp"
//#include "../../Core/Components/LedStrips.hpp"
//#include "../../Common/Components/LedStrip/LedStripDriver.hpp"
//#include "../../Common/Components/LedStrip/LedStripModel.hpp"
#include "../../Common/Components/I2c/I2c.hpp"
#include "../Messages/Message.hpp"
#include "../../Common/Components/Lcd1602Display/Lcd1602DisplayDriver.hpp"
#include "../../Common/Components/Lcd1602Display/Lcd1602DisplayModel.hpp"
#include "../../Common/Components/Tm1637/Tm1637Driver.hpp"
#include "../../Common/Components/Tm1637/Tm1637Model.hpp"

// I2cTask::I2cTask(RtosTask* rtosTask, 
//     RtosQueue& i2cQueue,
//     ComponentsBuilder::FraxisComponents& fraxisComponents, 
//     ComponentsBuilder::Models& models, 
//     ComponentsBuilder::Drivers& drivers)
//     : _rtosTask(rtosTask), _i2cQueue(i2cQueue),
//       _fraxisComponents(fraxisComponents), _models(models), _drivers(drivers)
// {
// }

// void I2cTask::SetRtosTask(RtosTask* rtosTask)
// {
//     _rtosTask = rtosTask;
// }

void I2cTask::Run()
{
    while (true)
    {
        // _rtosTask->DelayTask(1);

        // Message message;
        // if (_i2cQueue.Receive(&message, 1))
        // {
        //     switch (message.id)
        //     {
        //     case Message::EId::I2c_Initialize:
        //         _drivers.i2c->Initialize();
        //         break;

        //     case Message::EId::Lcd1602Display_Initialize:
        //         _drivers.lcd1602DisplayDriver->Initialize();
        //         break;

        //     case Message::EId::Lcd1602Display_TextLines:
        //         _drivers.lcd1602DisplayDriver->Update();
        //         break;

        //     case Message::EId::Tm1637_Initialize:
        //         switch (message.tm1637_Initialize_Parameters.id)
        //         {
        //         case Message::ETm1637Id::CentralPanel: _drivers.tm1637CentralPanel->Initialize(); break;
        //         case Message::ETm1637Id::Player1: _drivers.tm1637Player1->Initialize(); break;
        //         case Message::ETm1637Id::Player2: _drivers.tm1637Player2->Initialize(); break;
        //         }
        //         break;

        //     case Message::EId::Tm1637_Time:
        //         switch (message.tm1637_Time_Parameters.id)
        //         {
        //         case Message::ETm1637Id::CentralPanel: _drivers.tm1637CentralPanel->Write(); break;
        //         case Message::ETm1637Id::Player1: _drivers.tm1637Player1->Write(); break;
        //         case Message::ETm1637Id::Player2: _drivers.tm1637Player2->Write(); break;
        //         }
        //         break;

        //     case Message::EId::Tm1637_Value:
        //         switch (message.tm1637_Value_Parameters.id)
        //         {
        //         case Message::ETm1637Id::CentralPanel: _drivers.tm1637CentralPanel->Write(); break;
        //         case Message::ETm1637Id::Player1: _drivers.tm1637Player1->Write(); break;
        //         case Message::ETm1637Id::Player2: _drivers.tm1637Player2->Write(); break;
        //         }
        //         break;
            
        //     default:
        //         // Ignore others
        //         break;            
        //     }
        //}
    }
}