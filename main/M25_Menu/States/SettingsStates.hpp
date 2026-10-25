#pragma once

#include <chrono>
#include <cstdint>

class States;
class ApplicationsManager;

class SettingsStates
{
public:
    SettingsStates(
        States& states,
        ApplicationsManager& applicationsManager);
    ~SettingsStates() = default;

    void CheckSyncNvsSettings();

private:
    const std::chrono::microseconds NVS_SYNC_TIME = std::chrono::microseconds(10'000'000);

    States& _states;
    ApplicationsManager& _applicationsManager;

    std::chrono::microseconds _timeSinceNvsSync;
};
