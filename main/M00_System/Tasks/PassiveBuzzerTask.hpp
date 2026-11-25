#pragma once
#include "../../M60_DeviceDrivers/PassiveBuzzer/PassiveBuzzerTaskDeviceDriversDelegate.hpp"
#include "../../M90_Utilities/Task/Task.hpp"

class Context;
class RtosTask;

class PassiveBuzzerQueueReader;

namespace M60::Buzzer
{
    class PassiveBuzzerTaskDeviceDriversDelegate;
}

namespace M90::Assert
{
    class IAssert;
}

namespace M90::Log
{
    class ILog;
}

namespace M90::String
{
    class IStringUtilities;
}

class PassiveBuzzerTask : public M90::Task::Task
{
public:
    explicit PassiveBuzzerTask(
        PassiveBuzzerQueueReader& passiveBuzzerQueueReader, 
        M60::PassiveBuzzer::PassiveBuzzerTaskDeviceDriversDelegate&
            passiveBuzzerTaskDeviceDriversDelegate,
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log);

    PassiveBuzzerTask(
        const PassiveBuzzerTask&) = delete;
    
    PassiveBuzzerTask& operator=(
        const PassiveBuzzerTask&) = delete;
    
    PassiveBuzzerTask(
        PassiveBuzzerTask&&) = delete;
    
    PassiveBuzzerTask& operator=(
        PassiveBuzzerTask&&) = delete;

    ~PassiveBuzzerTask() override = default;

    void Initialize() override;
    
    void Run() override;
    
    static void TaskEntry(
        void* param);

private:
    PassiveBuzzerQueueReader& _passiveBuzzerQueueReader;

    M60::PassiveBuzzer::PassiveBuzzerTaskDeviceDriversDelegate&
        _passiveBuzzerTaskDeviceDriversDelegate;
};
