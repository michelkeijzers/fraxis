#pragma once

#include "../../M40_DomainModels/LedStrips/LedStripsQueueReader.hpp"
#include "../../M60_DeviceDrivers/Ws28xx/Ws28xxTaskDeviceDriversDelegate.hpp"
#include "../../M90_Utilities/Task/Task.hpp"

namespace M60::Ws28xx
{
    class IWs28xxDeviceDriver;
}

namespace M90::Assert
{
    class IAssert;
}

namespace M90::Log
{
    class Ilog;
}

namespace M90::String
{
    class IStringUtilities;
}

class Context;
class RtosTask;
class LedStrips;
class LedStripsQueue;

class LedStripsTask : public M90::Task::Task
{
public:
    explicit LedStripsTask(
        LedStripsQueueReader& ledStripsQueueReader,
        M60::Ws28xx::Ws28xxTaskDeviceDriversDelegate& ws28xxTaskDeviceDriversDelegate,
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log);

    LedStripsTask(
        const LedStripsTask&) = delete;
    
    LedStripsTask& operator=(
        const LedStripsTask&) = delete;
    
    LedStripsTask(
        LedStripsTask&&) = delete;
    
    LedStripsTask& operator=(
        LedStripsTask&&) = delete;

    ~LedStripsTask() override = default;
    
    void Initialize() override;

    void Run() override;
    
    static void TaskEntry(
        void* param);

private:
    LedStripsQueueReader& _ledStripsQueueReader;

    M60::Ws28xx::Ws28xxTaskDeviceDriversDelegate& _ws28xxTaskDeviceDriversDelegate;
};
