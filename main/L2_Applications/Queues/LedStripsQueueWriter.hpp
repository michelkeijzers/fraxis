#pragma once

class LedStripsQueue;
class ApplicationsManager;

class LedStripsQueueWriter
{
public:
    LedStripsQueueWriter(LedStripsQueue& i2cInputQueue, ApplicationsManager& applicationsManager);
    ~LedStripsQueueWriter();
    
private:
    LedStripsQueue& _ledStripsQueue;
    ApplicationsManager& _applicationsManager;
};
