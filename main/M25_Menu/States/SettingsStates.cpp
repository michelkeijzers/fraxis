#include "SettingsStates.hpp"
#include "../../M20_Applications/Applications/Application.hpp"
#include "../../M20_Applications/ApplicationsManager.hpp"
#include "../../M90_Utilities/Time/TimeUtilities.hpp"
#include <cstdint>

SettingsStates::SettingsStates(
    ApplicationsManager& applicationsManager)
    :
    _applicationsManager(applicationsManager),
    _timeSinceNvsSync(M90::Time::TimeUtilities::GetCurrentTimeInUs())
{
}

void SettingsStates::CheckSyncNvsSettings()
{
    if (std::chrono::microseconds elapsedMsSinceNvsSync =
        M90::Time::TimeUtilities::GetUsSince(_timeSinceNvsSync);
        elapsedMsSinceNvsSync >= NVS_SYNC_TIME)
    {
        _applicationsManager.SyncNvsSettings();
        _applicationsManager.SyncNvsApplicationsInfo();
    }
}
