#pragma once

#include "../M30_Messages/Types.hpp"
#include <cstdint>
#include <chrono>

class DiagnosticsManager;

namespace M90::Time
{
    class ITimeUtilities;
}

class WatchDog
{
public:
    const static std::chrono::microseconds APPLICATIONS_TASK_HEARTBEAT_TIMEOUT_US;
    
    const static std::chrono::microseconds DIAGNOSTICS_TASK_HEARTBEAT_TIMEOUT_US;

    const static std::chrono::microseconds I2C_TASK_HEARTBEAT_TIMEOUT_US;

    const static std::chrono::microseconds I2S_TASK_HEARTBEAT_TIMEOUT_US;
    
    const static std::chrono::microseconds LED_STRIPS_TASK_HEARTBEAT_TIMEOUT_US;

    const static std::chrono::microseconds PASSIVE_BUZZER_TASK_HEARTBEAT_TIMEOUT_US;

    const static std::chrono::microseconds SEVEN_SEGMENTS_DISPLAYS_TASK_HEARTBEAT_TIMEOUT_US;

    const static std::chrono::microseconds SPI_TASK_HEARTBEAT_TIMEOUT_US;

    WatchDog(
        DiagnosticsManager& diagnosticsManager,
        M90::Time::ITimeUtilities& timeUtilities);

    WatchDog(
        const WatchDog&) = delete;
    
    WatchDog& operator=(
        const WatchDog&) = delete;
    
    WatchDog(
        WatchDog&&) = delete;
    
    WatchDog& operator=(
        WatchDog&&) = delete;

    virtual ~WatchDog() = default;

    void OnHeartBeat(
        Types::ETaskId taskId, 
        std::chrono::microseconds timeStamp);

    void CheckTimeouts();

private:
    DiagnosticsManager& _diagnosticsManager;   

    std::chrono::microseconds _lastApplicationsTaskHeartBeatTimeStamp;
    
    std::chrono::microseconds _lastDiagnosticsTaskHeartBeatTimeStamp;

    std::chrono::microseconds _lastI2cTaskHeartBeatTimeStamp;
    
    std::chrono::microseconds _lastI2sTaskHeartBeatTimeStamp;

    std::chrono::microseconds _lastLedStripsTaskHeartBeatTimeStamp;

    std::chrono::microseconds _lastPassiveBuzzerTaskHeartBeatTimeStamp;

    std::chrono::microseconds _lastSevenSegmentsDisplaysTaskHeartBeatTimeStamp;

    std::chrono::microseconds _lastSpiTaskHeartBeatTimeStamp;

    M90::Time::ITimeUtilities& _timeUtilities;
};
