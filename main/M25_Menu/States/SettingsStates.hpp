#pragma once

#include <chrono>
#include <cstdint>

class States;
class ApplicationsManager;

class SettingsStates
{
public:
    explicit SettingsStates(
        ApplicationsManager& applicationsManager);

    SettingsStates(const SettingsStates&) = delete;
    SettingsStates& operator=(const SettingsStates&) = delete;
    SettingsStates(SettingsStates&&) = delete;
    SettingsStates& operator=(SettingsStates&&) = delete;

    ~SettingsStates() = default;

    void CheckSyncNvsSettings();

private:
    const std::chrono::microseconds NVS_SYNC_TIME = std::chrono::microseconds(10'000'000);

    ApplicationsManager& _applicationsManager;

    std::chrono::microseconds _timeSinceNvsSync;
};
