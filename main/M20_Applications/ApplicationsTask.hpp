#pragma once

#include "ApplicationsManager.hpp"
#include "Nvs/NvsSettings.hpp"
#include "Nvs/NvsApplicationsInfo.hpp"
#include "Queues/I2cInputQueueReader.hpp"
#include "Queues/I2cOutputQueueWriter.hpp"
#include "Queues/I2sOutputQueueWriter.hpp"
#include "Queues/LedStripsQueueWriter.hpp"
#include "Queues/PassiveBuzzerQueueWriter.hpp"
#include "Queues/SevenSegmentsDisplaysQueueWriter.hpp"

#include "Queues/SpiInputQueueReader.hpp"
#include "Queues/SpiOutputQueueWriter.hpp"
#include "Queues/QueueWriters.hpp"
#include "../M81_RtosServices/RtosTask/RtosTask.hpp"
#include "../M90_Utilities/Task/Task.hpp"

namespace M90::Assert
{
    class IAssert;
}

namespace M90::Log
{
    class ILog;
}

namespace M90::Time
{
    class ITimeUtilities;
}

class Context;
class ApplicationsManager;
class LedStripsQueue;
class I2cInputQueue;
class I2cOutputQueue;
class I2sOutputQueue;
class PassiveBuzzerQueue;
class SevenSegmentsDisplaysQueue;
class SpiInputQueue;
class SpiOutputQueue;

class ApplicationsTask : public M90::Task::Task
{
public:
    ApplicationsTask(
        Context& context,
        M80::Random::IRandom& random,
        M90::Assert::IAssert& assert,
        M90::Container::IContainerUtilities& containerUtilities,
        M90::Log::ILog& log,
        M90::Math::IMathUtilities& mathUtilities,
        M90::String::IStringUtilities& stringUtilities,
        M90::Time::ITimeUtilities& timeUtilities);

    ApplicationsTask(
        const ApplicationsTask&) = delete;
    
    ApplicationsTask& operator=(
        const ApplicationsTask&) = delete;
    
    ApplicationsTask(
        ApplicationsTask&&) = delete;
    
    ApplicationsTask& operator=(
        ApplicationsTask&&) = delete;

    ~ApplicationsTask() override= default;

    void Initialize() override;
    
    void Run() override;
    
    static void TaskEntry(
        void* param);

private:
    Context& _context;

    M90::Assert::IAssert& _assert;

    ApplicationsManager _applicationsManager;

    I2cInputQueue& _i2cInputQueue;
    
    I2cInputQueueReader _i2cInputQueueReader;

    I2cOutputQueue& _i2cOutputQueue;
    
    I2cOutputQueueWriter _i2cOutputQueueWriter;

    I2sOutputQueue& _i2sOutputQueue;

    I2sOutputQueueWriter _i2sOutputQueueWriter;
    
    PassiveBuzzerQueue& _passiveBuzzerQueue;

    PassiveBuzzerQueueWriter _passiveBuzzerQueueWriter;

    SevenSegmentsDisplaysQueue& _sevenSegmentsDisplaysQueue;

    SevenSegmentsDisplaysQueueWriter _sevenSegmentsDisplaysQueueWriter;

    SpiInputQueue& _spiInputQueue;
    
    SpiInputQueueReader _spiInputQueueReader;

    SpiOutputQueue& _spiOutputQueue;
    
    SpiOutputQueueWriter _spiOutputQueueWriter;

    LedStripsQueue& _ledStripsQueue;
    
    LedStripsQueueWriter _ledStripsQueueWriter;

    QueueWriters _queueWriters;

    NvsSettings _nvsSettings;
    
    NvsApplicationsInfo _nvsApplicationsInfo;
};
