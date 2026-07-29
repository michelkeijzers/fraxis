#pragma once

#include "../../L3_Messages/I2cOutputQueue.hpp"
#include <cstdint>
#include <string>

class QueueWriters;

class Send
{
public:
    Send(QueueWriters& queueWriters);
    ~Send();

    void Led(Types::ELedId ledId, bool state);
    void Line(uint8_t lineNumber, std::string line);
    
    void Value(Types::ETm1637Id tm1637Id, uint32_t value);
    void Time(Types::ETm1637Id tm1637Id, uint8_t first, uint8_t second);

private:
    QueueWriters& _queueWriters;
};
