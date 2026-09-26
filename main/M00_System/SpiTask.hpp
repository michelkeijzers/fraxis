#pragma once

#include "../M40_DomainModels/Spi/SpiOutputQueueReader.hpp"
#include "../M60_DeviceDrivers/SpiTaskDeviceDriversDelegate.hpp"
#include "../M90_Utilities/Task/Task.hpp"

class Context;
class RtosTask;
class MicroSdCard;
class SpiOutputQueue;

class SpiTask : public Task
{
public:
    explicit SpiTask(
        Context& context);
    ~SpiTask() = default;

    void Initialize() override;
    void Run() override;
    static void TaskEntry(
        void* param);

private:
    Context& _context;
    MicroSdCard& _microSdCard;
    
    SpiOutputQueue& _spiOutputQueue;
    SpiOutputQueueReader _spiOutputQueueReader;

    SpiTaskDeviceDriversDelegate _spiTaskDeviceDriversDelegate;
};
