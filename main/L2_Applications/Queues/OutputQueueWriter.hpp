#pragma once

#include <cstdint>
#include <string>

class OutputQueue;
class ApplicationsManager;

class OutputQueueWriter
{
public:
    OutputQueueWriter(OutputQueue& outputQueue, ApplicationsManager& applicationsManager);
    ~OutputQueueWriter();
    
    void SendLcd2004Line(uint8_t lineNumber, std::string line);

private:
    OutputQueue& _outputQueue;
    ApplicationsManager& _applicationsManager;  
};
