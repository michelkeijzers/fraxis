#pragma once

#include "../../L3_Messages/OutputQueue.hpp"
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

private:
    QueueWriters& _queueWriters;
};
