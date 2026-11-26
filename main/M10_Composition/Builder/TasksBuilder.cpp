#include "TasksBuilder.hpp"
#include "../Context/Context.hpp"
#include "../Context/ServicesContext.hpp"
#include "../../M00_System/Tasks/DiagnosticsTask.hpp"
#include "../../M00_System/Tasks/I2cTask.hpp"
#include "../../M00_System/Tasks/I2sTask.hpp"
#include "../../M00_System/Tasks/LedStripsTask.hpp"
#include "../../M00_System/Tasks/PassiveBuzzerTask.hpp"
#include "../../M00_System/Tasks/SevenSegmentsDisplaysTask.hpp"
#include "../../M00_System/Tasks/SpiTask.hpp"
#include "../../M00_System/Queues/DiagnosticsQueueWriter.hpp"
#include "../../M20_Applications/ApplicationsTask.hpp"
#include "../../M81_RtosServices/Rtos/Rtos.hpp"

#include <memory>

TasksBuilder::TasksBuilder(
    Context& context)
: 
    _context(context) 
{
    // No actions required.
}

void TasksBuilder::BuildTasksContext(
    WatchDog& watchDog,
    DiagnosticsQueueReader& diagnosticsQueueReader,
    I2cOutputQueueReader& i2cOutputQueueReader,
    I2sOutputQueueReader& i2sOutputQueueReader,
    LedStripsQueueReader& ledStripsQueueReader,
    SpiOutputQueueReader& spiOutputQueueReader,
    PassiveBuzzerQueueReader& passiveBuzzerQueueReader,
    M60::I2c::I2cTaskDeviceDriversDelegate& i2cTaskDeviceDriversDelegate,
    M60::I2s::I2sTaskDeviceDriversDelegate& i2sTaskDeviceDriversDelegate,
    M60::PassiveBuzzer::PassiveBuzzerTaskDeviceDriversDelegate&
        passiveBuzzerTaskDeviceDriversDelegate,
    M60::Spi::SpiTaskDeviceDriversDelegate& spiTaskDeviceDriversDelegate,
    M60::Ws28xx::Ws28xxTaskDeviceDriversDelegate& ws28xxTaskDeviceDriversDelegate,
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
    M90::Time::ITimeUtilities& timeUtilities)
{
    auto applicationsTask = CreateApplicationsTask(
        random,
        assert,
        containerUtilities,
        log,
        mathUtilities,
        stringUtilities,
        timeUtilities);

    auto diagnosticsTask = CreateDiagnosticsTask(
        watchDog,
        diagnosticsQueueReader,
        uart,
        assert,
        log);

    auto i2cTask = CreateI2cTask(
        i2cOutputQueueReader,
        i2cTaskDeviceDriversDelegate,
        assert,
        log);

    auto i2sTask = CreateI2sTask(
        i2sOutputQueueReader,
        i2sTaskDeviceDriversDelegate,
        assert,
        log);

    auto ledStripsTask = CreateLedStripsTask(
        ledStripsQueueReader,
        ws28xxTaskDeviceDriversDelegate,
        assert,
        log);

    auto passiveBuzzerTask = CreatePassiveBuzzerTask(
        passiveBuzzerQueueReader,
        passiveBuzzerTaskDeviceDriversDelegate,
        assert,
        log);

    auto sevenSegmentsDisplaysTask = CreateSevenSegmentsDisplaysTask(
        tm1637DeviceDriverCentralPanel,
        tm1637DeviceDriverPlayer1,
        tm1637DeviceDriverPlayer2,
        assert,
        log,
        stringUtilities,
        timeUtilities);

    auto spiTask = CreateSpiTask(
        spiOutputQueueReader,
        spiTaskDeviceDriversDelegate,
        assert,
        log);

    _context.GetTasks().Set(
        std::move(applicationsTask),
        std::move(i2cTask),
        std::move(spiTask),
        std::move(ledStripsTask),
        std::move(diagnosticsTask),
        std::move(i2sTask),
        std::move(passiveBuzzerTask),
        std::move(sevenSegmentsDisplaysTask));
}

std::unique_ptr<ApplicationsTask> TasksBuilder::CreateApplicationsTask(
    M80::Random::IRandom& random,
    M90::Assert::IAssert& assert,
    M90::Container::IContainerUtilities& containerUtilities,
    M90::Log::ILog& log,
    M90::Math::IMathUtilities& mathUtilities,
    M90::String::IStringUtilities& stringUtilities,
    M90::Time::ITimeUtilities& timeUtilities)
{
    constexpr const char* TASK_NAME = "Applications Task";
    constexpr uint16_t TASK_STACK_SIZE = 16384;
    constexpr uint8_t TASK_PRIORITY = 3;
    constexpr uint8_t TASK_CORE = 1;

    // Declare 16KB stack, because NVS keeps arrays of favorites/nr of starts/last start times and
    // checks against them.
    // This alone is twice: (4 + 2 + 1) * nr of applications.

    auto applicationsTask = std::make_unique<ApplicationsTask>(
        _context,
        random,
        assert,
        containerUtilities,
        log,
        mathUtilities,
        stringUtilities,
        timeUtilities);
    auto& applicationsTaskRef = *applicationsTask;

    ServicesContext& servicesContext = _context.GetServices();
    M81::RtosTask::IRtosTask* applicationsRtosTask = servicesContext.GetRtos().CreateTask(
        ApplicationsTask::TaskEntry,
        TASK_NAME,
        TASK_STACK_SIZE,
        TASK_PRIORITY,
        TASK_CORE,
        applicationsTask.get());
    applicationsTaskRef.SetRtosTask(*applicationsRtosTask);

    return applicationsTask;
}

std::unique_ptr<DiagnosticsTask> TasksBuilder::CreateDiagnosticsTask(
    WatchDog& watchDog,
    DiagnosticsQueueReader& diagnosticsQueueReader,
    M80::Uart::IUart& uart,
    M90::Assert::IAssert& assert,
    M90::Log::ILog& log)
{
    constexpr const char* TASK_NAME = "Diagnostics Task";
    constexpr uint16_t TASK_STACK_SIZE = 4096;
    constexpr uint8_t TASK_PRIORITY = 3;
    constexpr uint8_t TASK_CORE = 1;

    auto diagnosticsTask = std::make_unique<DiagnosticsTask>(
        watchDog, 
        diagnosticsQueueReader, 
        uart, 
        assert, 
        log);
    auto& diagnosticsTaskRef = *diagnosticsTask;

    ServicesContext& servicesContext = _context.GetServices();
    M81::RtosTask::IRtosTask* diagnosticsRtosTask = servicesContext.GetRtos().CreateTask(
        DiagnosticsTask::TaskEntry,
        TASK_NAME,
        TASK_STACK_SIZE,
        TASK_PRIORITY,
        TASK_CORE,
        diagnosticsTask.get());
    diagnosticsTaskRef.SetRtosTask(*diagnosticsRtosTask);

    return diagnosticsTask;
}

std::unique_ptr<I2cTask> TasksBuilder::CreateI2cTask(
    I2cOutputQueueReader& i2cOutputQueueReader,
    M60::I2c::I2cTaskDeviceDriversDelegate& i2cTaskDeviceDriversDelegate,
    M90::Assert::IAssert& assert,
    M90::Log::ILog& log)
{
    constexpr const char* TASK_NAME = "I2C Task";
    constexpr uint16_t TASK_STACK_SIZE = 4096;
    constexpr uint8_t TASK_PRIORITY = 3;
    constexpr uint8_t TASK_CORE = 1;
      
    auto i2cTask = std::make_unique<I2cTask>(
        i2cOutputQueueReader,
        i2cTaskDeviceDriversDelegate,
        assert,
        log);

    auto& i2cTaskRef = *i2cTask;

    ServicesContext& servicesContext = _context.GetServices();
    M81::RtosTask::IRtosTask* i2cRtosTask = servicesContext.GetRtos().CreateTask(
        I2cTask::TaskEntry,
        TASK_NAME,
        TASK_STACK_SIZE,
        TASK_PRIORITY,
        TASK_CORE,
        i2cTask.get());
    i2cTaskRef.SetRtosTask(*i2cRtosTask);

    return i2cTask;
}

std::unique_ptr<I2sTask> TasksBuilder::CreateI2sTask(
    I2sOutputQueueReader& i2sOutputQueueReader,
    M60::I2s::I2sTaskDeviceDriversDelegate& i2sTaskDeviceDriversDelegate,
    M90::Assert::IAssert& assert,
    M90::Log::ILog& log)
{
    constexpr const char* TASK_NAME = "I2S Task";
    constexpr uint16_t TASK_STACK_SIZE = 4096;
    constexpr uint8_t TASK_PRIORITY = 3;
    constexpr uint8_t TASK_CORE = 1;

    auto i2sTask = std::make_unique<I2sTask>(
        i2sOutputQueueReader,
        i2sTaskDeviceDriversDelegate,
        assert,
        log);
    auto& i2sTaskRef = *i2sTask;

    ServicesContext& servicesContext = _context.GetServices();
    M81::RtosTask::IRtosTask* i2sRtosTask = servicesContext.GetRtos().CreateTask(
        I2sTask::TaskEntry,
        TASK_NAME,
        TASK_STACK_SIZE,
        TASK_PRIORITY,
        TASK_CORE,
        i2sTask.get());
    i2sTaskRef.SetRtosTask(*i2sRtosTask);

    return i2sTask;
}

std::unique_ptr<LedStripsTask> TasksBuilder::CreateLedStripsTask(
    LedStripsQueueReader& ledStripsQueueReader,
    M60::Ws28xx::Ws28xxTaskDeviceDriversDelegate& ws28xxTaskDeviceDriversDelegate,
    M90::Assert::IAssert& assert,
    M90::Log::ILog& log)
{
    constexpr const char* TASK_NAME = "LedStrips Task";
    constexpr uint16_t TASK_STACK_SIZE = 4096;
    constexpr uint8_t TASK_PRIORITY = 3;
    constexpr uint8_t TASK_CORE = 1;

    auto ledStripsTask = std::make_unique<LedStripsTask>(
        ledStripsQueueReader,
        ws28xxTaskDeviceDriversDelegate,
        assert,
        log);
    auto& ledStripsTaskRef = *ledStripsTask;

    ServicesContext& servicesContext = _context.GetServices();
    M81::RtosTask::IRtosTask* ledStripsRtosTask = servicesContext.GetRtos().CreateTask(
        LedStripsTask::TaskEntry,
        TASK_NAME,
        TASK_STACK_SIZE,
        TASK_PRIORITY,
        TASK_CORE,
        ledStripsTask.get());
    ledStripsTaskRef.SetRtosTask(*ledStripsRtosTask);

    return ledStripsTask;
}

std::unique_ptr<PassiveBuzzerTask> TasksBuilder::CreatePassiveBuzzerTask(
    PassiveBuzzerQueueReader& passiveBuzzerQueueReader,
    M60::PassiveBuzzer::PassiveBuzzerTaskDeviceDriversDelegate& 
        passiveBuzzerTaskDeviceDriversDelegate,
    M90::Assert::IAssert& assert,
    M90::Log::ILog& log)
{
    constexpr const char* TASK_NAME = "Passive Buzzer Task";
    constexpr uint16_t TASK_STACK_SIZE = 4096;
    constexpr uint8_t TASK_PRIORITY = 3;
    constexpr uint8_t TASK_CORE = 1;

    auto passiveBuzzerTask = std::make_unique<PassiveBuzzerTask>(
        passiveBuzzerQueueReader,
        passiveBuzzerTaskDeviceDriversDelegate,
        assert,
        log);
    auto& passiveBuzzerTaskRef = *passiveBuzzerTask;

    ServicesContext& servicesContext = _context.GetServices();
    M81::RtosTask::IRtosTask* passiveBuzzerRtosTask = servicesContext.GetRtos().CreateTask(
        PassiveBuzzerTask::TaskEntry,
        TASK_NAME,
        TASK_STACK_SIZE,
        TASK_PRIORITY,
        TASK_CORE,
        passiveBuzzerTask.get());
    passiveBuzzerTaskRef.SetRtosTask(*passiveBuzzerRtosTask);

    return passiveBuzzerTask;
}

std::unique_ptr<SevenSegmentsDisplaysTask> TasksBuilder::CreateSevenSegmentsDisplaysTask(
    M60::SevenSegmentsDisplays::Tm1637DeviceDriver& tm1637DeviceDriverCentralPanel,
    M60::SevenSegmentsDisplays::Tm1637DeviceDriver& tm1637DeviceDriverPlayer1,
    M60::SevenSegmentsDisplays::Tm1637DeviceDriver& tm1637DeviceDriverPlayer2,
    M90::Assert::IAssert& assert,
    M90::Log::ILog& log,
    M90::String::IStringUtilities& stringUtilities,
    M90::Time::ITimeUtilities& timeUtilities)
{
    constexpr const char* TASK_NAME = "Seven Segments Displays Task";
    constexpr uint16_t TASK_STACK_SIZE = 4096;
    constexpr uint8_t TASK_PRIORITY = 3;
    constexpr uint8_t TASK_CORE = 1;

    auto sevenSegmentsDisplaysTask = std::make_unique<SevenSegmentsDisplaysTask>(
        _context,
        tm1637DeviceDriverCentralPanel,
        tm1637DeviceDriverPlayer1,
        tm1637DeviceDriverPlayer2,
        assert,
        log,
        stringUtilities,
        timeUtilities);
    auto& sevenSegmentsDisplaysTaskRef = *sevenSegmentsDisplaysTask;

    ServicesContext& servicesContext = _context.GetServices();
    M81::RtosTask::IRtosTask* sevenSegmentsDisplaysRtosTask = servicesContext.GetRtos().CreateTask(
        SevenSegmentsDisplaysTask::TaskEntry,
        TASK_NAME,
        TASK_STACK_SIZE,
        TASK_PRIORITY,
        TASK_CORE,
        sevenSegmentsDisplaysTask.get());
    sevenSegmentsDisplaysTaskRef.SetRtosTask(*sevenSegmentsDisplaysRtosTask);

    return sevenSegmentsDisplaysTask;
}

std::unique_ptr<SpiTask> TasksBuilder::CreateSpiTask(
    SpiOutputQueueReader& spiOutputQueueReader,
    M60::Spi::SpiTaskDeviceDriversDelegate& spiTaskDeviceDriversDelegate,
    M90::Assert::IAssert& assert,
    M90::Log::ILog& log)
{
    constexpr const char* TASK_NAME = "SPI Task";
    constexpr uint16_t TASK_STACK_SIZE = 4096;
    constexpr uint8_t TASK_PRIORITY = 3;
    constexpr uint8_t TASK_CORE = 1;

    auto spiTask = std::make_unique<SpiTask>(
        spiOutputQueueReader,
        spiTaskDeviceDriversDelegate,
        assert,
        log);
    auto& spiTaskRef = *spiTask;

    ServicesContext& servicesContext = _context.GetServices();
    M81::RtosTask::IRtosTask* spiRtosTask = servicesContext.GetRtos().CreateTask(
        SpiTask::TaskEntry,
        TASK_NAME,
        TASK_STACK_SIZE,
        TASK_PRIORITY,
        TASK_CORE,
        spiTask.get());
    spiTaskRef.SetRtosTask(*spiRtosTask);

    return spiTask;
}
