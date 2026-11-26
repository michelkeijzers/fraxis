#pragma once

#include "../../M40_DomainModels/Spi/SpiOutputQueueReader.hpp"
#include "../../M60_DeviceDrivers/Spi/SpiTaskDeviceDriversDelegate.hpp"
#include "../../M90_Utilities/Task/Task.hpp"

namespace M90::Assert
{
    class IAssert;
}

namespace M90::Log
{
    class Ilog;
}

class RtosTask;
class MicroSdCard;
class SpiOutputQueue;
class SpiInputQueueWriter;

class SpiTask : public M90::Task::Task
{
public:
    explicit SpiTask(
        SpiOutputQueueReader& spiOutputQueueReader,
        M60::Spi::SpiTaskDeviceDriversDelegate& spiTaskDeviceDriversDelegate,
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log);

    SpiTask(
        const SpiTask&) = delete;
    
    SpiTask& operator=(
        const SpiTask&) = delete;
    
    SpiTask(
        SpiTask&&) = delete;
    
    SpiTask& operator=(
        SpiTask&&) = delete;

    ~SpiTask() override = default;

    void Initialize() override;
    
    void Run() override;
    
    static void TaskEntry(
        void* param);

private:
    SpiOutputQueueReader& _spiOutputQueueReader;

    M60::Spi::SpiTaskDeviceDriversDelegate& _spiTaskDeviceDriversDelegate;
};
