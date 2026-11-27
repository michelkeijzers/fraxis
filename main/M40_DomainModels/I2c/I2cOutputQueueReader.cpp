#include "I2cOutputQueueReader.hpp"
#include "IoPins/IoPins.hpp"
#include "Lcd2004/Lcd2004.hpp"
#include "../SevenSegmentsDisplays/Tm1637.hpp"
#include "../../M50_DeviceModels/SevenSegmentsDisplays/Tm1637/Tm1637DeviceModel.hpp"
#include "../../M30_Messages/I2c/I2cOutputQueue.hpp"
#include "../../M81_RtosServices/RtosQueue/RtosQueue.hpp"
#include "../../M90_Utilities/Assert/Assert.hpp"

I2cOutputQueueReader::I2cOutputQueueReader(
    M90::Assert::IAssert &assert,
    M90::Log::ILog& log,
    M90::String::IStringUtilities& stringUtilities,
    I2cOutputQueue& i2cOutputQueue, 
    Lcd2004& lcd2004, 
    IoPins& ioPins)
:  
    QueueProcessor(assert, log, stringUtilities),
    _lcd2004(lcd2004), 
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
                _lcd2004.SetLine(message.lcd2004Line.number, message.lcd2004Line.content.data());
                break;

            default:
                GetAssert().Fail(Types::ETaskId::I2cTask, "Unknown message type");
                break;
        }
        handled = true;
    }
    return handled;
}
