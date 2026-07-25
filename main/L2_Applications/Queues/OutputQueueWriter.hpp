#pragma once

class OutputQueue;
class ApplicationsManager;

class OutputQueueWriter
{
public:
    OutputQueueWriter(OutputQueue& outputQueue, ApplicationsManager& applicationsManager);
    ~OutputQueueWriter();
    
private:
    OutputQueue& _outputQueue;
    ApplicationsManager& _applicationsManager;  
};
