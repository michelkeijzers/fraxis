#pragma once

#include "../../M40_DomainModels/I2s/I2sMicrophone/I2sMicrophone.hpp"
#include "../../M40_DomainModels/I2s/I2sDac/I2sDac.hpp"
#include "../../M40_DomainModels/I2s/I2sOutputQueueReader.hpp"
#include "../../M60_DeviceDrivers/I2s/I2sTaskDeviceDriversDelegate.hpp"
#include "../../M90_Utilities/Task/Task.hpp"

class Context;
class RtosTask;
class I2sOutputQueue;
class PassiveBuzzer;

class I2sTask : public M90::Task::Task
{
public:
    explicit I2sTask(
        Context& context,
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log,
        M90::String::IStringUtilities& stringUtilities);

    I2sTask(
        const I2sTask&) = delete;
    
    I2sTask& operator=(
        const I2sTask&) = delete;
    
    I2sTask(
        I2sTask&&) = delete;
    
    I2sTask& operator=(
        I2sTask&&) = delete;

    ~I2sTask() override = default;

    void Initialize() override;
    
    void Run() override;
    
    static void TaskEntry(
        void* param);

private:
    Context& _context;
    
    I2sMicrophone& _i2sMicrophone;
    
    I2sDac& _i2sDac;
    
    PassiveBuzzer& _passiveBuzzer;

    I2sOutputQueue& _i2sOutputQueue;
    
    I2sOutputQueueReader _i2sOutputQueueReader;

    M60::I2s::I2sTaskDeviceDriversDelegate _i2sTaskDeviceDriversDelegate;
};
