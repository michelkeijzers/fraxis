#include "I2cOutputQueueReader.hpp"
#include "IoPins/IoPins.hpp"
#include "Displays/Lcd2004/Lcd2004.hpp"
#include "Displays/Tm1637/Tm1637.hpp"
#include "../I2c/Displays/Tm1637/Tm1637.hpp"
#include "../../L5_DeviceModels/Tm1637/Tm1637DeviceModel.hpp"
#include "../../L3_Messages/I2cOutputQueue.hpp"
#include "../../L9_Utilities/Assert/Assert.hpp"
#include "../../L9_Utilities/Assert/Assert.hpp"

I2cOutputQueueReader::I2cOutputQueueReader(
    I2cOutputQueue& i2cOutputQueue, 
    Lcd2004& lcd2004, 
    Tm1637& tm1637CentralPanel, 
    Tm1637& tm1637Player1, 
    Tm1637& tm1637Player2, 
    IoPins& ioPins)
:   _lcd2004(lcd2004), 
    _tm1637CentralPanel(tm1637CentralPanel), 
    _tm1637Player1(tm1637Player1), 
    _tm1637Player2(tm1637Player2), 
    _ioPins(ioPins)
{
    SetQueue(i2cOutputQueue);
}

I2cOutputQueueReader::~I2cOutputQueueReader() 
{
}

I2cOutputQueue& I2cOutputQueueReader::GetI2cOutputQueue()
{
    return static_cast<I2cOutputQueue&>(GetQueue());
}

bool I2cOutputQueueReader::HandleMessage() 
{
    Log::Pointer("HM CP",&(_tm1637CentralPanel.GetTm1637DeviceModel()));
    Log::Pointer("   P1", &_tm1637Player1.GetTm1637DeviceModel());
    Log::Pointer("   P2", &_tm1637Player2.GetTm1637DeviceModel());

    bool handled = false;

    I2cOutputQueue::OutputMessage outputMessage = {};
    auto& queue = GetI2cOutputQueue();
    RtosQueue& rtosQueue = queue.GetRtosQueue();
    if (rtosQueue.Receive(&outputMessage, 0))
    {
        switch (outputMessage.type)
        {
            case I2cOutputQueue::OutputMessage::EType::Led:
                _ioPins.GetLedById(outputMessage.led.ledId).SetState(outputMessage.led.state);
                break;

            case I2cOutputQueue::OutputMessage::EType::Lcd2004Line:
                _lcd2004.SetLine(outputMessage.lcd2004Line.lineNumber, outputMessage.lcd2004Line.lineContent);
                break;

            case I2cOutputQueue::OutputMessage::EType::Tm1637Value:
            {
                Log::Pointer("HM CP", &(_tm1637CentralPanel.GetTm1637DeviceModel()));
                Log::Pointer("4  P1", &_tm1637Player1.GetTm1637DeviceModel());
                Log::Pointer("   P2", &_tm1637Player2.GetTm1637DeviceModel());
                Log::Text("Tm1637 Value");
                Tm1637& tm1637 = GetTm1637ById(outputMessage.tm1637Value.tm1637Id);
                tm1637.SetValue(outputMessage.tm1637Value.value);
                Log::Pointer("HM CP", &(_tm1637CentralPanel.GetTm1637DeviceModel()));
                Log::Pointer("5  P1", &_tm1637Player1.GetTm1637DeviceModel());
                Log::Pointer("   P2", &_tm1637Player2.GetTm1637DeviceModel());
            }
            break;

            case I2cOutputQueue::OutputMessage::EType::Tm1637Time:
            {
                Log::Text("Tm1637 Time");
                Tm1637& tm1637 = GetTm1637ById(outputMessage.tm1637Time.tm1637Id);
                 Assert::Equals(tm1637.GetTm1637DeviceModel().GetNrOfDigits(), 4, "digits");
                tm1637.SetTime(outputMessage.tm1637Time.first, outputMessage.tm1637Time.second);
            }
            break;

            default:
                Assert::Fail("Unknown message type");
                break;
        }
        handled = true;
    }
    return handled;
}

Tm1637& I2cOutputQueueReader::GetTm1637ById(Types::ETm1637Id tm1637Id)
{
    switch (tm1637Id)
    {

        case Types::ETm1637Id::CentralPanel: return _tm1637CentralPanel;  break;
        case Types::ETm1637Id::Player1:      return _tm1637Player1;       break;
        case Types::ETm1637Id::Player2:      return _tm1637Player2;       break;
        default:
            Assert::Fail("Unknown tm1637 id");
            return _tm1637CentralPanel;
    }
}
