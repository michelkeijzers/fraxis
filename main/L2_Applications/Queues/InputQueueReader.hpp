#pragma once

class InputQueue;
class ApplicationsManager;

class InputQueueReader
{
public:
    InputQueueReader(InputQueue& inputQueue, ApplicationsManager& applicationsManager);
    ~InputQueueReader();
    
    bool HandleMessage();

private:
    InputQueue& _inputQueue;
    ApplicationsManager& _applicationsManager;
};
