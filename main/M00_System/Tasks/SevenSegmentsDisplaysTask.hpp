#pragma once

#include "../../M40_DomainModels/SevenSegmentsDisplays/SevenSegmentsDisplaysQueueReader.hpp"
#include "../../M60_DeviceDrivers/SevenSegmentsDisplays/SevenSegmentsDisplaysTaskDeviceDriversDelegate.hpp"
#include "../../M90_Utilities/Task/Task.hpp"

namespace M90::Assert
{
    class IAssert;
}

namespace M90::Log
{
    class ILog;
}

class SevenSegmentsDisplaysTask : public M90::Task::Task
{
public:
    SevenSegmentsDisplaysTask(
        SevenSegmentsDisplaysQueueReader& sevenSegmentsDisplaysQueueReader,
        M60::SevenSegmentsDisplays::SevenSegmentsDisplaysTaskDeviceDriversDelegate& 
            sevenSegmentsDisplaysTaskDeviceDriversDelegate,
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log);

    SevenSegmentsDisplaysTask(
        const SevenSegmentsDisplaysTask&) = delete;
    
    SevenSegmentsDisplaysTask& operator=(
        const SevenSegmentsDisplaysTask&) = delete;
    
    SevenSegmentsDisplaysTask(
        SevenSegmentsDisplaysTask&&) = delete;
    
    SevenSegmentsDisplaysTask& operator=(
        SevenSegmentsDisplaysTask&&) = delete;

    ~SevenSegmentsDisplaysTask() override = default;

    void Initialize() override;
    
    void Run() override;
    
    static void TaskEntry(
        void* param);

private:
    SevenSegmentsDisplaysQueueReader& _sevenSegmentsDisplaysQueueReader;

    M60::SevenSegmentsDisplays::SevenSegmentsDisplaysTaskDeviceDriversDelegate&
        _sevenSegmentsDisplaysTaskDeviceDriversDelegate;
};
