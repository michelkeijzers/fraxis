#include "SettingsStates.hpp"
#include "../../M20_Applications/Applications/Application.hpp"
#include "../../M20_Applications/ApplicationsManager.hpp"
#include "../../M90_Utilities/Time/TimeUtilities.hpp"
#include <cstdint>

SettingsStates::SettingsStates(
    States& states,
    ApplicationsManager& applicationsManager)
    :
    _states(states),
    _applicationsManager(applicationsManager),
    _timeSinceNvsSync(TimeUtilities::GetCurrentTimeInUs())
{
}

void SettingsStates::CheckSyncNvsSettings()
{
    if (std::chrono::microseconds elapsedMsSinceNvsSync =
        TimeUtilities::GetUsSince(_timeSinceNvsSync);
        elapsedMsSinceNvsSync >= NVS_SYNC_TIME)
    {
        _applicationsManager.SyncNvsSettings();
    }
}
