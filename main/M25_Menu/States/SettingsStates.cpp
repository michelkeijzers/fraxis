#include "SettingsStates.hpp"
#include "../../M20_Applications/Applications/Application.hpp"
#include "../../M20_Applications/ApplicationsManager.hpp"
#include "../../M90_Utilities/Time/TimeUtilities.hpp"
#include <cstdint>

SettingsStates::SettingsStates(
    ApplicationsManager& applicationsManager,
    M90::Time::ITimeUtilities& timeUtilities)
:
    _applicationsManager(applicationsManager),
    _timeSinceNvsSync(timeUtilities.GetCurrentTimeInUs()),
    _timeUtilities(timeUtilities)
{
    //  No functionality required.
}

void SettingsStates::CheckSyncNvsSettings()
{
    if (std::chrono::microseconds elapsedMsSinceNvsSync =
        _timeUtilities.GetUsSince(_timeSinceNvsSync);
        elapsedMsSinceNvsSync >= NVS_SYNC_TIME)
    {
        _applicationsManager.SyncNvsSettings();
        _applicationsManager.SyncNvsApplicationsInfo();
    }
}
