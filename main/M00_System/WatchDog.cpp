#include "WatchDog.hpp"
#include "DiagnosticsManager.hpp"
#include "../M90_Utilities/Time/TimeUtilities.hpp"

const std::chrono::microseconds WatchDog::APPLICATIONS_TASK_HEARTBEAT_TIMEOUT_US = 
    std::chrono::microseconds(1'000'000); // 1 second
const std::chrono::microseconds WatchDog::DIAGNOSTICS_TASK_HEARTBEAT_TIMEOUT_US =
    std::chrono::microseconds(1'000'000); // 1 second
const std::chrono::microseconds WatchDog::I2C_TASK_HEARTBEAT_TIMEOUT_US =
    std::chrono::microseconds(1'000'000); // 1 second
const std::chrono::microseconds WatchDog::I2S_TASK_HEARTBEAT_TIMEOUT_US =
    std::chrono::microseconds(1'000'000); // 1 second
const std::chrono::microseconds WatchDog::LED_STRIPS_TASK_HEARTBEAT_TIMEOUT_US =
    std::chrono::microseconds(20'000); // 20 milliseconds
const std::chrono::microseconds WatchDog::PASSIVE_BUZZER_TASK_HEARTBEAT_TIMEOUT_US =
    std::chrono::microseconds(1'000'000); // 1 second
const std::chrono::microseconds WatchDog::SEVEN_SEGMENTS_DISPLAYS_TASK_HEARTBEAT_TIMEOUT_US =
    std::chrono::microseconds(1'000'000); // 1 second
const std::chrono::microseconds WatchDog::SPI_TASK_HEARTBEAT_TIMEOUT_US =
    std::chrono::microseconds(1'000'000); // 1 second

WatchDog::WatchDog(
    DiagnosticsManager& diagnosticsManager,
    M90::Time::ITimeUtilities& timeUtilities)
: 
    _diagnosticsManager(diagnosticsManager),
    _lastApplicationsTaskHeartBeatTimeStamp(
        APPLICATIONS_TASK_HEARTBEAT_TIMEOUT_US),
    _lastDiagnosticsTaskHeartBeatTimeStamp(
        DIAGNOSTICS_TASK_HEARTBEAT_TIMEOUT_US),
    _lastI2cTaskHeartBeatTimeStamp(
        I2C_TASK_HEARTBEAT_TIMEOUT_US),
    _lastI2sTaskHeartBeatTimeStamp(
        I2S_TASK_HEARTBEAT_TIMEOUT_US),
    _lastLedStripsTaskHeartBeatTimeStamp(
        LED_STRIPS_TASK_HEARTBEAT_TIMEOUT_US),
    _lastPassiveBuzzerTaskHeartBeatTimeStamp(
        PASSIVE_BUZZER_TASK_HEARTBEAT_TIMEOUT_US),
    _lastSevenSegmentsDisplaysTaskHeartBeatTimeStamp(
        SEVEN_SEGMENTS_DISPLAYS_TASK_HEARTBEAT_TIMEOUT_US),
    _lastSpiTaskHeartBeatTimeStamp(
        SPI_TASK_HEARTBEAT_TIMEOUT_US),
    _timeUtilities(timeUtilities)
{
    // No functionality required.
}

// MAKE AN INIT hERE THAT CALLS INIT OF DIAGNOSTICSMANAGER TO INIT UART

void WatchDog::OnHeartBeat(
    Types::ETaskId taskId, 
    std::chrono::microseconds timeStamp)
{
    using enum Types::ETaskId;
    switch (taskId)
    {
        case ApplicationsTask:
            _lastApplicationsTaskHeartBeatTimeStamp = timeStamp;
            break;

        case DiagnosticsTask:
            _lastDiagnosticsTaskHeartBeatTimeStamp = timeStamp;
            break;

        case I2cTask:
            _lastI2cTaskHeartBeatTimeStamp = timeStamp;
            break;

        case I2sTask:
            _lastI2sTaskHeartBeatTimeStamp = timeStamp;
            break;

        case LedStripsTask:
            _lastLedStripsTaskHeartBeatTimeStamp = timeStamp;
            break;

        case PassiveBuzzerTask:
            _lastPassiveBuzzerTaskHeartBeatTimeStamp = timeStamp;
            break;

        case SevenSegmentsDisplaysTask:
            _lastSevenSegmentsDisplaysTaskHeartBeatTimeStamp = timeStamp;
            break;

        case SpiTask:
            _lastSpiTaskHeartBeatTimeStamp = timeStamp;
            break;

        default:
            break;
    }   
}

void WatchDog::CheckTimeouts()
{
    std::chrono::microseconds currentTickCount = _timeUtilities.GetCurrentTimeInUs();
    if (_lastApplicationsTaskHeartBeatTimeStamp + APPLICATIONS_TASK_HEARTBEAT_TIMEOUT_US < 
        currentTickCount)
    {
        _diagnosticsManager.OnLogEntry(
            Types::ETaskId::DiagnosticsTask, 
            currentTickCount,
            Types::ELogLevel::Error,
            "ApplicationsTask heartbeat timeout");
    }

    if (_lastDiagnosticsTaskHeartBeatTimeStamp + DIAGNOSTICS_TASK_HEARTBEAT_TIMEOUT_US < 
        currentTickCount)
    {
        _diagnosticsManager.OnLogEntry(
            Types::ETaskId::DiagnosticsTask,
            currentTickCount,
            Types::ELogLevel::Error,
            "DiagnosticsTask heartbeat timeout");
    }

    if (_lastI2cTaskHeartBeatTimeStamp + I2C_TASK_HEARTBEAT_TIMEOUT_US < currentTickCount)
    {
        _diagnosticsManager.OnLogEntry(
            Types::ETaskId::DiagnosticsTask, 
            currentTickCount, 
            Types::ELogLevel::Error,
            "I2cTask heartbeat timeout");
    }

    if (_lastI2sTaskHeartBeatTimeStamp + I2S_TASK_HEARTBEAT_TIMEOUT_US < currentTickCount)
    {
        _diagnosticsManager.OnLogEntry(
            Types::ETaskId::DiagnosticsTask,
            currentTickCount,
            Types::ELogLevel::Error,
            "I2sTask heartbeat timeout");
    }

    if (_lastLedStripsTaskHeartBeatTimeStamp + LED_STRIPS_TASK_HEARTBEAT_TIMEOUT_US < 
        currentTickCount)
    {
        _diagnosticsManager.OnLogEntry(
            Types::ETaskId::DiagnosticsTask, 
            currentTickCount, 
            Types::ELogLevel::Error,
            "LedStripsTask heartbeat timeout");
    }

    if (_lastPassiveBuzzerTaskHeartBeatTimeStamp + PASSIVE_BUZZER_TASK_HEARTBEAT_TIMEOUT_US < 
        currentTickCount)
    {
        _diagnosticsManager.OnLogEntry(
            Types::ETaskId::DiagnosticsTask,
            currentTickCount,
            Types::ELogLevel::Error,
            "PassiveBuzzerTask heartbeat timeout");
    }

    if (_lastSevenSegmentsDisplaysTaskHeartBeatTimeStamp + 
        SEVEN_SEGMENTS_DISPLAYS_TASK_HEARTBEAT_TIMEOUT_US < currentTickCount)
    {
        _diagnosticsManager.OnLogEntry(
            Types::ETaskId::DiagnosticsTask,
            currentTickCount,
            Types::ELogLevel::Error,
            "SevenSegmentsDisplaysTask heartbeat timeout");
    }

    if (_lastSpiTaskHeartBeatTimeStamp + SPI_TASK_HEARTBEAT_TIMEOUT_US < currentTickCount)
    {
        _diagnosticsManager.OnLogEntry(
            Types::ETaskId::DiagnosticsTask,
            currentTickCount,
            Types::ELogLevel::Error,
            "SpiTask heartbeat timeout");
    }
}
