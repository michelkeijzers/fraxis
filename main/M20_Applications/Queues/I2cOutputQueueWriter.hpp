#pragma once

#include "../../M30_Messages/QueueProcessor.hpp"
#include "../../M30_Messages/Types.hpp"
#include "../../M40_DomainModels/I2c/Displays/Lcd2004/Lcd2004.hpp"
#include "../../M60_DeviceDrivers/Lcd2004/Lcd2004DeviceDriver.hpp"
#include <cstdint>
#include <string>
#include <array>

class I2cOutputQueue;
class ApplicationsManager;

class I2cOutputQueueWriter : public QueueProcessor
{
public:
    I2cOutputQueueWriter(
        I2cOutputQueue& i2cOutputQueue, 
        ApplicationsManager& applicationsManager);

    I2cOutputQueueWriter(const I2cOutputQueueWriter&) = delete;
    I2cOutputQueueWriter& operator=(const I2cOutputQueueWriter&) = delete;
    I2cOutputQueueWriter(I2cOutputQueueWriter&&) = delete;
    I2cOutputQueueWriter& operator=(I2cOutputQueueWriter&&) = delete;

    ~I2cOutputQueueWriter() override = default;
    
    void SendLed(
        Types::ELedId, 
        bool state);

    void SendLcd2004PredefinedCharacter(
        uint8_t slotIndex,
        uint8_t predefinedCharacterIndex);
    
    void SendLcd2004CustomCharacter(
        uint8_t slotIndex,
        std::array<uint8_t, Lcd2004::CUSTOM_CHARACTER_DATA_LENGTH> data);
    
    void SendLcd2004Line(
        uint8_t lineNumber, 
        std::string_view line);

    void SendTm1637Enable(
        Types::ETm1637Id tm1637Id,
        bool enable);

    void SendTm1637Brightness(
        Types::ETm1637Id tm1637Id, 
        uint8_t brightness);

    void SendTm1637Value(
        Types::ETm1637Id tm1637Id, 
        uint32_t value);
    
    void SendTm1637Time(
        Types::ETm1637Id tm1637Id,
        uint8_t first,
        uint8_t second);

private:
    I2cOutputQueue& GetI2cOutputQueue();

    ApplicationsManager& _applicationsManager;
};
