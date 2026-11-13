#pragma once

#include "../M40_DomainModels/LedStrips/LedStripsQueueReader.hpp"
#include "../M60_DeviceDrivers/Ws28xx/Ws28xxTaskDeviceDriversDelegate.hpp"
#include "../M90_Utilities/Task/Task.hpp"

class Context;
class RtosTask;
class LedStrips;
class LedStripsQueue;

class LedStripsTask : public M90::Task::Task
{
public:
    explicit LedStripsTask(
        Context& context);

    LedStripsTask(const LedStripsTask&) = delete;
    LedStripsTask& operator=(const LedStripsTask&) = delete;
    LedStripsTask(LedStripsTask&&) = delete;
    LedStripsTask& operator=(LedStripsTask&&) = delete;

    ~LedStripsTask() override = default;
    
    void Initialize() override;
    void Run() override;
    static void TaskEntry(
        void* param);

private:
    Context& _context;
    LedStrips& _ledStrips;

    LedStripsQueue& _ledStripsQueue;
    LedStripsQueueReader _ledStripsQueueReader;

    M60::Ws28xx::Ws28xxTaskDeviceDriversDelegate _ws28xxTaskDeviceDriversDelegate;
};
