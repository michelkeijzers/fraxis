#pragma once

#include "../../L3_Messages/I2cOutputQueue.hpp"
#include <cstdint>
#include <string>

class I2cOutputQueue;
class ApplicationsManager;

class I2cOutputQueueWriter
{
public:
    I2cOutputQueueWriter(I2cOutputQueue& i2cOutputQueue, ApplicationsManager& applicationsManager);
    ~I2cOutputQueueWriter();
    
    void SendLed(Types::ELedId, bool state);
    void SendLcd2004Line(uint8_t lineNumber, std::string_view line);

    void SendTm1637Value(Types::ETm1637Id tm1637Id, uint32_t value);
    void SendTm1637Time(Types::ETm1637Id tm1637Id, uint8_t first, uint8_t second);

private:
    I2cOutputQueue& _i2cOutputQueue;
    ApplicationsManager& _applicationsManager;  
};
