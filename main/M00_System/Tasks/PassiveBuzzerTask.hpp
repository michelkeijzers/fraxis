#pragma once

#include "../../M40_DomainModels/PassiveBuzzer/PassiveBuzzer.hpp"
#include "../../M40_DomainModels/PassiveBuzzer/PassiveBuzzerQueueReader.hpp"
#include "../../M60_DeviceDrivers/PassiveBuzzer/PassiveBuzzerTaskDeviceDriversDelegate.hpp"
#include "../../M90_Utilities/Task/Task.hpp"

class Context;
class RtosTask;
class PassiveBuzzerQueue;
class PassiveBuzzer;

namespace M90::String
{
    class IStringUtilities;
}

class PassiveBuzzerTask : public M90::Task::Task
{
public:
    explicit PassiveBuzzerTask(
        Context& context,
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log,
        M90::String::IStringUtilities& stringUtilities);

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
    Context& _context;
    
    PassiveBuzzer& _passiveBuzzer;

    PassiveBuzzerQueue& _passiveBuzzerQueue;
    
    PassiveBuzzerQueueReader _passiveBuzzerQueueReader;

    M60::PassiveBuzzer::PassiveBuzzerTaskDeviceDriversDelegate 
        _passiveBuzzerTaskDeviceDriversDelegate;
};
