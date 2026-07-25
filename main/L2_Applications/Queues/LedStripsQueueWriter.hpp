#pragma once

class LedStripsQueue;
class ApplicationsManager;

class LedStripsQueueWriter
{
public:
    LedStripsQueueWriter(LedStripsQueue& inputQueue, ApplicationsManager& applicationsManager);
    ~LedStripsQueueWriter();
    
private:
    LedStripsQueue& _ledStripsQueue;
    ApplicationsManager& _applicationsManager;
};
