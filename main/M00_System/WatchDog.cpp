#include "WatchDog.hpp"
#include "DiagnosticsManager.hpp"
#include "../M90_Utilities/Time/TimeUtilities.hpp"

const std::chrono::microseconds WatchDog::APPLICATIONS_TASK_HEARTBEAT_TIMEOUT_US = 
    std::chrono::microseconds(1'000'000); // 1 second
const std::chrono::microseconds WatchDog::I2C_TASK_HEARTBEAT_TIMEOUT_US = 
    std::chrono::microseconds(1'000'000); // 1 second
const std::chrono::microseconds WatchDog::LED_STRIPS_TASK_HEARTBEAT_TIMEOUT_US = 
    std::chrono::microseconds(20'000); // 20 milliseconds

WatchDog::WatchDog(
    DiagnosticsManager& diagnosticsManager)
:   _diagnosticsManager(diagnosticsManager),
    _lastApplicationsTaskHeartBeatTimeStamp(100'000),
    _lastI2cTaskHeartBeatTimeStamp(100'000),
    _lastLedStripsTaskHeartBeatTimeStamp(20'000)
{
}

void WatchDog::OnHeartBeat(
    Types::ETaskId taskId, 
    std::chrono::microseconds timeStamp)
{
    switch (taskId)
    {
        case Types::ETaskId::ApplicationsTask:
            _lastApplicationsTaskHeartBeatTimeStamp = timeStamp;
            break;

        case Types::ETaskId::I2cTask:
            _lastI2cTaskHeartBeatTimeStamp = timeStamp;
            break;

        case Types::ETaskId::LedStripsTask:
            _lastLedStripsTaskHeartBeatTimeStamp = timeStamp;
            break;

        default:
            break;
    }   
}

void WatchDog::CheckTimeouts()
{
    std::chrono::microseconds currentTickCount = TimeUtilities::GetCurrentTimeInUs();
    if (_lastApplicationsTaskHeartBeatTimeStamp + APPLICATIONS_TASK_HEARTBEAT_TIMEOUT_US < 
        currentTickCount)
    {
        _diagnosticsManager.OnLogEntry(
            Types::ETaskId::DiagnosticsTask, 
            currentTickCount,
            Types::ELogLevel::Error,
            "ApplicationsTask heartbeat timeout");
    }

    if (_lastI2cTaskHeartBeatTimeStamp + I2C_TASK_HEARTBEAT_TIMEOUT_US < currentTickCount)
    {
        _diagnosticsManager.OnLogEntry(
            Types::ETaskId::DiagnosticsTask, 
            currentTickCount, 
            Types::ELogLevel::Error,
            "I2cTask heartbeat timeout");
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
}
