#include "I2cOutputQueueWriter.hpp"
#include "../ApplicationsManager.hpp"
#include "../../M30_Messages/Types.hpp"
#include "../../M30_Messages/I2c/I2cOutputQueue.hpp"
#include "../../M40_DomainModels/I2c/Lcd2004/Lcd2004.hpp"
#include "../../M81_RtosServices/RtosQueue/RtosQueue.hpp"
#include "../../M90_Utilities/String/StringUtilities.hpp"

I2cOutputQueueWriter::I2cOutputQueueWriter(
    M90::Assert::IAssert& assert,
    M90::Log::ILog& log,
    M90::String::IStringUtilities& stringUtilities,
    I2cOutputQueue& i2cOutputQueue, 
    ApplicationsManager& applicationsManager) 
:   
    QueueProcessor(assert, log, stringUtilities),
    _applicationsManager(applicationsManager)
{
    SetQueue(i2cOutputQueue);
}

I2cOutputQueue& I2cOutputQueueWriter::GetI2cOutputQueue() 
{
    return static_cast<I2cOutputQueue&>(GetQueue()); 
}

void I2cOutputQueueWriter::SendLed(
    Types::ELedId ledId, 
    bool state)
{
    I2cOutputQueue::Message message {};
    message.type = I2cOutputQueue::Message::EType::Led;
    message.led.id = ledId;
    message.led.state = state;
    GetI2cOutputQueue().GetRtosQueue().Send(&message, 0);
}

void I2cOutputQueueWriter::SendLcd2004PredefinedCharacter(
    uint8_t slotIndex,
    uint8_t predefinedCharacterIndex)
{
    I2cOutputQueue::Message message {};
    message.type = I2cOutputQueue::Message::EType::Lcd2004PredefinedCharacter;
    message.lcd2004PredefinedCharacter.slotIndex = slotIndex;
    message.lcd2004PredefinedCharacter.predefinedCharacterIndex = predefinedCharacterIndex;
    GetI2cOutputQueue().GetRtosQueue().Send(&message, 0);
}

void I2cOutputQueueWriter::SendLcd2004CustomCharacter(
    uint8_t slotIndex,
    std::array<uint8_t, Lcd2004::CUSTOM_CHARACTER_DATA_LENGTH> data)
{
    I2cOutputQueue::Message message {};
    message.type = I2cOutputQueue::Message::EType::Lcd2004CustomCharacter;
    message.lcd2004CustomCharacter.slotIndex = slotIndex;
    for (uint8_t index = 0; index < 8; index++)
    {
        message.lcd2004CustomCharacter.data[index] = data[index];
    }
    GetI2cOutputQueue().GetRtosQueue().Send(&message, 0);
}

void I2cOutputQueueWriter::SendLcd2004Line(
    uint8_t lineNumber, 
    std::string_view line)
{
    I2cOutputQueue::Message message = {};
    message.type = I2cOutputQueue::Message::EType::Lcd2004Line;
    message.lcd2004Line.number = lineNumber;
    GetStringUtilities().CopyToBuffer(
        line, message.lcd2004Line.content.data(), Lcd2004::LINE_WIDTH + 1);
    GetI2cOutputQueue().GetRtosQueue().Send(&message, 0);
}
