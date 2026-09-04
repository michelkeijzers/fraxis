#include "WatchDog.hpp"
#include "DiagnosticsManager.hpp"
#include "../L9_Utilities/Time/TimeUtilities.hpp"

WatchDog::WatchDog(
    DiagnosticsManager& diagnosticsManager)
:   _diagnosticsManager(diagnosticsManager),
    _lastApplicationsTaskHeartBeatTimeStamp(0),
    _lastI2cTaskHeartBeatTimeStamp(0),
    _lastLedStripsTaskHeartBeatTimeStamp(0)
{
}

void WatchDog::OnHeartBeat(
    Types::ETaskId taskId, 
    uint64_t timeStamp)
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
    uint64_t currentTickCount = TimeUtilities::GetCurrentTimeInUs();
    if (_lastApplicationsTaskHeartBeatTimeStamp + APPLICATIONS_TASK_HEARTBEAT_TIMEOUT_MS < currentTickCount)
    {
        _diagnosticsManager.OnLogEntry(
            Types::ETaskId::DiagnosticsTask, 
            currentTickCount,
            Types::ELogLevel::Error,
            "ApplicationsTask heartbeat timeout");
    }

    if (_lastI2cTaskHeartBeatTimeStamp + I2C_TASK_HEARTBEAT_TIMEOUT_MS < currentTickCount)
    {
        _diagnosticsManager.OnLogEntry(
            Types::ETaskId::DiagnosticsTask, 
            currentTickCount, 
            Types::ELogLevel::Error,
            "I2cTask heartbeat timeout");
    }

    if (_lastLedStripsTaskHeartBeatTimeStamp + LED_STRIPS_TASK_HEARTBEAT_TIMEOUT_MS < currentTickCount)
    {
        _diagnosticsManager.OnLogEntry(
            Types::ETaskId::DiagnosticsTask, 
            currentTickCount, 
            Types::ELogLevel::Error,
            "LedStripsTask heartbeat timeout");
    }
}
