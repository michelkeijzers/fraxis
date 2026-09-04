#pragma once

#include "../L3_Messages/Types.hpp"
#include <cstdint>

class Context;
class DiagnosticsManager;

class WatchDog
{
public:
    const static uint16_t APPLICATIONS_TASK_HEARTBEAT_TIMEOUT_MS = 100; // ms
    const static uint16_t I2C_TASK_HEARTBEAT_TIMEOUT_MS = 100; // ms
    const static uint16_t LED_STRIPS_TASK_HEARTBEAT_TIMEOUT_MS = 20; // ms

    WatchDog(
        DiagnosticsManager& diagnosticsManager);
    virtual ~WatchDog() = default;

    void OnHeartBeat(
        Types::ETaskId taskId, 
        uint64_t timeStamp);

    void CheckTimeouts();

private:
    DiagnosticsManager& _diagnosticsManager;   

    uint64_t _lastApplicationsTaskHeartBeatTimeStamp = 0;
    uint64_t _lastI2cTaskHeartBeatTimeStamp = 0;
    uint64_t _lastLedStripsTaskHeartBeatTimeStamp = 0;
};
