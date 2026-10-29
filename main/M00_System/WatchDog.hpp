#pragma once

#include "../M30_Messages/Types.hpp"
#include <cstdint>
#include <chrono>

class Context;
class DiagnosticsManager;

class WatchDog
{
public:
    const static std::chrono::microseconds  APPLICATIONS_TASK_HEARTBEAT_TIMEOUT_US;
    const static std::chrono::microseconds I2C_TASK_HEARTBEAT_TIMEOUT_US;
    const static std::chrono::microseconds LED_STRIPS_TASK_HEARTBEAT_TIMEOUT_US;

    explicit WatchDog(
        DiagnosticsManager& diagnosticsManager);

    WatchDog(const WatchDog&) = delete;
    WatchDog& operator=(const WatchDog&) = delete;
    WatchDog(WatchDog&&) = delete;
    WatchDog& operator=(WatchDog&&) = delete;

    virtual ~WatchDog() = default;

    void OnHeartBeat(
        Types::ETaskId taskId, 
        std::chrono::microseconds timeStamp);

    void CheckTimeouts();

private:
    DiagnosticsManager& _diagnosticsManager;   

    std::chrono::microseconds _lastApplicationsTaskHeartBeatTimeStamp;
    std::chrono::microseconds _lastI2cTaskHeartBeatTimeStamp;
    std::chrono::microseconds _lastLedStripsTaskHeartBeatTimeStamp;
};
