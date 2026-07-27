#pragma once

#include "../../L3_Messages/OutputQueue.hpp"
#include <cstdint>
#include <string>

class OutputQueue;
class ApplicationsManager;

class OutputQueueWriter
{
public:
    OutputQueueWriter(OutputQueue& outputQueue, ApplicationsManager& applicationsManager);
    ~OutputQueueWriter();
    
    void SendLed(Types::ELedId, bool state);
    void SendLcd2004Line(uint8_t lineNumber, std::string line);

private:
    OutputQueue& _outputQueue;
    ApplicationsManager& _applicationsManager;  
};
