#pragma once

#include "../M40_DomainModels/LedStrips/LedStripsQueueReader.hpp"
#include "../M60_DeviceDrivers/LedStripsTaskDeviceDriversDelegate.hpp"
#include "../M90_Utilities/Task/Task.hpp"

class Context;
class RtosTask;
class LedStrips;
class LedStripsQueue;

class LedStripsTask : public Task
{
public:
    explicit LedStripsTask(
        Context& context);
    ~LedStripsTask() = default;
    
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
