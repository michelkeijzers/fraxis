#pragma once

#include <memory>

class I2cOutputQueue;
class I2cOutputQueueReader;
class IoPins;
class Lcd2004;
class Mcp23017DeviceModel;

namespace M60::I2c
{
    class Lcd2004DeviceDriver;
    class Mcp23017DeviceDriver;
    class I2cTaskDeviceDriversDelegate;
}

namespace M60::PassiveBuzzer
{
    class PassiveBuzzerTaskDeviceDriversDelegate;
}

namespace M60::SevenSegmentsDisplays
{
    class Tm1637DeviceDriver;
}


namespace M60::Ws28xx
{
    class IWs28xxDeviceDriver;
    class Ws28xxTaskDeviceDriversDelegate;
}

namespace M80::Random
{
    class IRandom;
}

namespace M80::Uart
{
    class IUart;
}

namespace M90::Assert
{
    class IAssert;
}

namespace M90::Container
{
    class IContainerUtilities;
}

namespace M90::Log
{
    class ILog;
}

namespace M90::Math
{
    class IMathUtilities;
}

namespace M90::String
{
    class IStringUtilities;
}

namespace M90::Time
{
    class ITimeUtilities;
}

class WatchDog;
class I2cOutputQueue;
class I2cOutputQueueReader;
class LedStripsQueueReader;
class SpiInputQueueWriter;
class IoPins;
class Lcd2004;
class Mcp23017DeviceModel;
class Context;
class ApplicationsTask;
class DiagnosticsQueue;
class DiagnosticsQueueReader;
class DiagnosticsTask;
class I2cTask;
class I2sTask;
class LedStripsTask;
class PassiveBuzzer;
class PassiveBuzzerQueue;
class PassiveBuzzerQueueReader;
class PassiveBuzzerTask;
class SevenSegmentsDisplaysTask;
class SpiTask;

class TasksBuilder
{
public:
    explicit TasksBuilder(
        Context& context);

    TasksBuilder(
        const TasksBuilder&) = delete;
    
    TasksBuilder& operator=(
        const TasksBuilder&) = delete;
    
    TasksBuilder(
        TasksBuilder&&) = delete;
    
    TasksBuilder& operator=(
        TasksBuilder&&) = delete;

    virtual ~TasksBuilder() = default;

    void BuildTasksContext(
        WatchDog& watchDog,
        DiagnosticsQueueReader& diagnosticsQueueReader,
        I2cOutputQueueReader& i2cOutputQueueReader,
        LedStripsQueueReader& ledStripsQueueReader,
        SpiInputQueueWriter& spiInputQueueWriter,
        PassiveBuzzerQueueReader& passiveBuzzerQueueReader,
        M60::PassiveBuzzer::PassiveBuzzerTaskDeviceDriversDelegate& 
            passiveBuzzerTaskDeviceDriversDelegate,
        M60::Ws28xx::Ws28xxTaskDeviceDriversDelegate& ws28xxTaskDeviceDriversDelegate,
        M60::I2c::I2cTaskDeviceDriversDelegate& i2cTaskDeviceDriversDelegate,
        M60::SevenSegmentsDisplays::Tm1637DeviceDriver& tm1637DeviceDriverCentralPanel,
        M60::SevenSegmentsDisplays::Tm1637DeviceDriver& tm1637DeviceDriverPlayer1,
        M60::SevenSegmentsDisplays::Tm1637DeviceDriver& tm1637DeviceDriverPlayer2,
        M80::Random::IRandom& random,
        M80::Uart::IUart& uart,
        M90::Assert::IAssert& assert,
        M90::Container::IContainerUtilities& containerUtilities,
        M90::Log::ILog& log,
        M90::Math::IMathUtilities& mathUtilities,
        M90::String::IStringUtilities& stringUtilities,
        M90::Time::ITimeUtilities& timeUtilities);

private:
    Context& _context;

    std::unique_ptr<ApplicationsTask> CreateApplicationsTask(
        M80::Random::IRandom& random,
        M90::Assert::IAssert& assert,
        M90::Container::IContainerUtilities& containerUtilities,
        M90::Log::ILog& log,
        M90::Math::IMathUtilities& mathUtilities,
        M90::String::IStringUtilities& stringUtilities,
        M90::Time::ITimeUtilities& timeUtilities);

    std::unique_ptr<DiagnosticsTask> CreateDiagnosticsTask(
        WatchDog& watchDog,
        DiagnosticsQueueReader& diagnosticsQueueReader,
        M80::Uart::IUart& uart,
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log);

    std::unique_ptr<I2cTask> CreateI2cTask(
        I2cOutputQueueReader& i2cOutputQueueReader,
        M60::I2c::I2cTaskDeviceDriversDelegate& i2cTaskDeviceDriversDelegate,
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log);

    std::unique_ptr<I2sTask> CreateI2sTask(
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log,
        M90::String::IStringUtilities& stringUtilities);

    std::unique_ptr<LedStripsTask> CreateLedStripsTask(
        LedStripsQueueReader& ledStripsQueueReader,
        M60::Ws28xx::Ws28xxTaskDeviceDriversDelegate& ws28xxTaskDeviceDriversDelegate,
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log);

    std::unique_ptr<PassiveBuzzerTask> CreatePassiveBuzzerTask(
        PassiveBuzzerQueueReader& passiveBuzzerQueueReader,
        M60::PassiveBuzzer::PassiveBuzzerTaskDeviceDriversDelegate& 
            passiveBuzzerTaskDeviceDriversDelegate,
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log);

    std::unique_ptr<SevenSegmentsDisplaysTask> CreateSevenSegmentsDisplaysTask(
        M60::SevenSegmentsDisplays::Tm1637DeviceDriver& tm1637DeviceDriverCentralPanel,
        M60::SevenSegmentsDisplays::Tm1637DeviceDriver& tm1637DeviceDriverPlayer1,
        M60::SevenSegmentsDisplays::Tm1637DeviceDriver& tm1637DeviceDriverPlayer2,
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log,
        M90::String::IStringUtilities& stringUtilities,
        M90::Time::ITimeUtilities& timeUtilities);

    std::unique_ptr<SpiTask> CreateSpiTask(
        SpiInputQueueWriter& spiInputQueueWriter,
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log,
        M90::String::IStringUtilities& stringUtilities);
};
