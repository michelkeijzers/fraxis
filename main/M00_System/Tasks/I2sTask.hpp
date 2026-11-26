#pragma once

#include "../../M40_DomainModels/I2s/I2sMicrophone/I2sMicrophone.hpp"
#include "../../M40_DomainModels/I2s/I2sDac/I2sDac.hpp"
#include "../../M40_DomainModels/I2s/I2sOutputQueueReader.hpp"
#include "../../M60_DeviceDrivers/I2s/I2sTaskDeviceDriversDelegate.hpp"
#include "../../M90_Utilities/Task/Task.hpp"

class I2sOutputQueueReaeder;

namespace M60::I2s
{
    class I2sTaskDeviceDriversDelegate;
}

class I2sTask : public M90::Task::Task
{
public:
    I2sTask(
        I2sOutputQueueReader& i2sOutputQueueReader,
        M60::I2s::I2sTaskDeviceDriversDelegate& i2sTaskDeviceDriversDelegate,
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log);
        
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
    I2sOutputQueueReader& _i2sOutputQueueReader;

    M60::I2s::I2sTaskDeviceDriversDelegate& _i2sTaskDeviceDriversDelegate;
};
