#pragma once

#include "../../L3_Messages/QueueProcessor.hpp"

class LedStripsQueue;
class ApplicationsManager;

class LedStripsQueueWriter : public QueueProcessor
{
public:
    LedStripsQueueWriter(LedStripsQueue& i2cInputQueue, ApplicationsManager& applicationsManager);
    ~LedStripsQueueWriter();
    
private:
    LedStripsQueue& _ledStripsQueue;
    ApplicationsManager& _applicationsManager;
};
