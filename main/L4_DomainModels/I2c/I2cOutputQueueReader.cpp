#include "I2cOutputQueueReader.hpp"
#include "IoPins/IoPins.hpp"
#include "Displays/Lcd2004/Lcd2004.hpp"
#include "Displays/Tm1637/Tm1637.hpp"
#include "../../L5_DeviceModels/Tm1637/Tm1637DeviceModel.hpp"
#include "../../L3_Messages/I2cOutputQueue.hpp"
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

I2cOutputQueue& I2cOutputQueueReader::GetI2cOutputQueue()
{
    return static_cast<I2cOutputQueue&>(GetQueue());
}

bool I2cOutputQueueReader::HandleMessage() 
{
    bool handled = false;

    I2cOutputQueue::Message message = {};
    auto& queue = GetI2cOutputQueue();
    if (auto& rtosQueue = queue.GetRtosQueue(); rtosQueue.Receive(&message, 0))
    {
        switch (message.type)
        {
            case I2cOutputQueue::Message::EType::Led:
                _ioPins.GetLedById(message.led.id).SetState(message.led.state);
                break;

            case I2cOutputQueue::Message::EType::Lcd2004PredefinedCharacter:
                _lcd2004.SetPredefinedCharacter(message.lcd2004PredefinedCharacter.slotIndex,
                    message.lcd2004PredefinedCharacter.predefinedCharacterIndex);
                break;

            case I2cOutputQueue::Message::EType::Lcd2004CustomCharacter:
                _lcd2004.SetCustomCharacter(message.lcd2004CustomCharacter.slotIndex,
                    message.lcd2004CustomCharacter.data);
                break;

            case I2cOutputQueue::Message::EType::Lcd2004Line:
                _lcd2004.SetLine(message.lcd2004Line.number, message.lcd2004Line.content);
                break;

            case I2cOutputQueue::Message::EType::Tm1637Value:
            {
                Tm1637& tm1637 = GetTm1637ById(message.tm1637Value.id);
                tm1637.SetValue(message.tm1637Value.value);
            }
            break;

            case I2cOutputQueue::Message::EType::Tm1637Time:
            {
                Tm1637& tm1637 = GetTm1637ById(message.tm1637Time.id);
                 Assert::Equals(
                    Types::ETaskId::I2cTask, 
                    tm1637.GetTm1637DeviceModel().GetNrOfDigits(), 
                    4, 
                    "digits");
                tm1637.SetTime(message.tm1637Time.first, message.tm1637Time.second);
            }
            break;

            default:
                Assert::Fail(Types::ETaskId::I2cTask, "Unknown message type");
                break;
        }
        handled = true;
    }
    return handled;
}

Tm1637& I2cOutputQueueReader::GetTm1637ById(
    Types::ETm1637Id tm1637Id)
{
    using enum Types::ETm1637Id;
    switch (tm1637Id)
    {
        case CentralPanel: return _tm1637CentralPanel;  break;
        case Player1:      return _tm1637Player1;       break;
        case Player2:      return _tm1637Player2;       break;
        default:
            Assert::Fail(Types::ETaskId::I2cTask, "Unknown tm1637 id");
            return _tm1637CentralPanel;
    }
}
