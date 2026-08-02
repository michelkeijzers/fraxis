#pragma once

#include "../L4_DomainModels/LedStrips/LedStripsQueueReader.hpp"
#include "../L6_DeviceDrivers/LedStripsTaskDeviceDriversDelegate.hpp"
#include "../L9_Utilities/Task/Task.hpp"

class Context;
class RtosTask;
class LedStrips;
class LedStripsQueue;

class LedStripsTask : public Task
{
public:
    LedStripsTask(
        Context& context);
    ~LedStripsTask();
    
    void Initialize() override;
    void Run() override;
    static void TaskEntry(
        void* param);

private:
    Context& _context;
    LedStrips& _ledStrips;

    LedStripsQueue& _ledStripsQueue;
    LedStripsQueueReader _ledStripsQueueReader;

    LedStripsTaskDeviceDriversDelegate _ledStripsTaskDeviceDriversDelegate;
};
