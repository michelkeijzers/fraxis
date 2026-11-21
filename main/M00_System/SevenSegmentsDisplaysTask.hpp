#pragma once

#include "../M40_DomainModels/SevenSegmentsDisplays/SevenSegmentsDisplaysQueueReader.hpp"
#include "../M60_DeviceDrivers/SevenSegmentsDisplays/SevenSegmentsDisplaysTaskDeviceDriversDelegate.hpp"
#include "../M90_Utilities/Task/Task.hpp"

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

namespace M90::Time
{
    class ITimeUtilities;
}

namespace M60::SevenSegmentsDisplays
{
    class Tm1637;
}

class Context;
class RtosTask;
class Tm1637;
class SevenSegmentsDisplaysQueue;

class SevenSegmentsDisplaysTask : public M90::Task::Task
{
public:
    SevenSegmentsDisplaysTask(
        Context& context,
        M60::SevenSegmentsDisplays::Tm1637DeviceDriver& tm1637DeviceDriverCentralPanel,
        M60::SevenSegmentsDisplays::Tm1637DeviceDriver& tm1637DeviceDriverPlayer1,
        M60::SevenSegmentsDisplays::Tm1637DeviceDriver& tm1637DeviceDriverPlayer2,
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log,
        M90::String::IStringUtilities& stringUtilities,
        M90::Time::ITimeUtilities& timeUtilities);

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
    Context& _context;

    M90::Assert::IAssert& _assert;

    Tm1637& _tm1637CentralPanel;
    
    Tm1637& _tm1637Player1;
    
    Tm1637& _tm1637Player2;
    
    SevenSegmentsDisplaysQueue& _sevenSegmentsDisplaysQueue;
    
    SevenSegmentsDisplaysQueueReader _sevenSegmentsDisplaysQueueReader;

    M60::SevenSegmentsDisplays::SevenSegmentsDisplaysTaskDeviceDriversDelegate 
        _sevenSegmentsDisplaysTaskDeviceDriversDelegate;
};
