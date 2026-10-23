#include "NvsAppsInfo.hpp"
#include "../ApplicationsManager.hpp"
#include "../Menu/MenuApplication.hpp"
#include "../../M10_Composition/Context/Context.hpp"
#include "../../M80_Services/Nvs/Nvs.hpp"
#include "../../M90_Utilities/Assert/Assert.hpp"
#include "../../M90_Utilities/Log/Log.hpp"

const std::string NvsAppsInfo::NAMESPACE = "apps_info";

const std::string NvsAppsInfo::FAVORITES_KEY = "favorites";
const std::string NvsAppsInfo::NR_OF_TIMES_STARTED_KEY = "nr_of_times_sta";
const std::string NvsAppsInfo::LAST_START_TIMES_KEY = "last_start_tims";

NvsAppsInfo::NvsAppsInfo(    
    Context& context, 
    ApplicationsManager& applicationsManager)
:
    _context(context),
    _applicationsManager(applicationsManager),
    _favorites(),
    _nrOfTimesStarted(),
    _lastStartTimes(),
    _favoritesDirty(false),
    _nrOfTimesStartedDirty(false),
    _lastStartTimesDirty(false)
{
}

void NvsAppsInfo::Read()
{
    auto& nvs = _context.GetServices().GetNvs();
    nvs.SetNamespace(NAMESPACE);
    ReadFavorites();
    ReadNrOfTimesStarted();
    ReadLastStartTimes();
    nvs.Close();
}

/// @brief Reads the favorites. If there is a size mismatch, write all values.
void NvsAppsInfo::ReadFavorites()
{
    auto& nvs = _context.GetServices().GetNvs();
    if (size_t size = sizeof(_favorites); nvs.ReadBlob(
        FAVORITES_KEY, 
        reinterpret_cast<uint8_t*>(_favorites.data()), // NOSONAR: std::byte
        size))
    {
        // No action needed.
    }
    else
    {
        Assert::IsTrue(Types::ETaskId::System, 
            nvs.WriteBlob(
                FAVORITES_KEY, 
                reinterpret_cast<uint8_t*>(_favorites.data()), // NOSONAR: std::byte
                size),
            "Failed to write favorites.");
    }

    _favoritesDirty = false;
}

/// @brief Reads the number of times the application has been started. If there is a size mismatch, write all values.
void NvsAppsInfo::ReadNrOfTimesStarted()
{
    auto& nvs = _context.GetServices().GetNvs();
    if (size_t size = sizeof(_nrOfTimesStarted); nvs.ReadBlob(
        NR_OF_TIMES_STARTED_KEY,
        reinterpret_cast<uint8_t*>(_nrOfTimesStarted.data()), // NOSONAR: std::byte
        size))
    {
        // No action needed.
    }
    else
    {
        Assert::IsTrue(Types::ETaskId::System,
            nvs.WriteBlob(
                NR_OF_TIMES_STARTED_KEY,
                reinterpret_cast<uint8_t*>(_nrOfTimesStarted.data()), // NOSONAR: std::byte
                size),
            "Failed to write NrOfTimesStarted.");
    }

    _nrOfTimesStartedDirty = false;
}

/// @brief Reads the last start times of the applications. If there is a size mismatch, write all values.
void NvsAppsInfo::ReadLastStartTimes()
{
    auto& nvs = _context.GetServices().GetNvs();
    if (size_t size = sizeof(_lastStartTimes); nvs.ReadBlob(
        LAST_START_TIMES_KEY,
        reinterpret_cast<uint8_t*>(_lastStartTimes.data()), // NOSONAR S9545: std::byte
        size))
    {
        // No action needed.
    }
    else
    {
        Assert::IsTrue(Types::ETaskId::System,
            nvs.WriteBlob(
                LAST_START_TIMES_KEY,
                reinterpret_cast<uint8_t*>(_lastStartTimes.data()), // NOSONAR S9545: std::byte
                size),
            "Failed to write LastStartTimes.");
    }

    
    _lastStartTimesDirty = false;
}

bool NvsAppsInfo::GetFavorite(
    uint16_t applicationIndex) const
{
    Assert::IsTrue(
        Types::ETaskId::System, 
        applicationIndex < NR_OF_APPLICATIONS, 
        "applicationIndex not in range");
    return _favorites[applicationIndex]; // NOSONAR S6385: overflowing indes
}

void NvsAppsInfo::SetFavorite(
    uint16_t applicationIndex,
    bool favorite)
{
    Assert::IsTrue(
        Types::ETaskId::System,
        applicationIndex < NR_OF_APPLICATIONS,
        "applicationIndex not in range");
    if (_favorites[applicationIndex] != favorite) // NOSONAR S6385 index vs length
    {
        _favorites[applicationIndex] = favorite; // NOSONAR S686 array overrun
        _favoritesDirty = true;
    }
}

uint16_t NvsAppsInfo::GetNrOfTimesStarted(
    uint16_t applicationIndex) const
{
    Assert::IsTrue(
        Types::ETaskId::System,
        applicationIndex < NR_OF_APPLICATIONS,
        "applicationIndex not in range");
    return _nrOfTimesStarted[applicationIndex]; // NOSONAR S6385 index vs length
}

void NvsAppsInfo::IncreaseNrOfTimesStarted(
    uint16_t applicationIndex)
{
    Assert::IsTrue(
        Types::ETaskId::System,
        applicationIndex < NR_OF_APPLICATIONS,
        "applicationIndex not in range");
    if (_nrOfTimesStarted[applicationIndex] < UINT16_MAX) // NOSONAR S6385 index vs length
    {
        _nrOfTimesStarted[applicationIndex]++; 
        _nrOfTimesStartedDirty = true;
    }
}

uint32_t NvsAppsInfo::GetLastStartTime(
    uint16_t applicationIndex) const
{
    Assert::IsTrue(
        Types::ETaskId::System,
        applicationIndex < NR_OF_APPLICATIONS,
        "applicationIndex not in range");
    return _lastStartTimes[applicationIndex]; // NOSONAR S6385 index vs length
}

void NvsAppsInfo::SetLastStartTime(
    uint16_t applicationIndex,
    uint32_t lastStartTime)
{
    Assert::IsTrue(
        Types::ETaskId::System,
        applicationIndex < NR_OF_APPLICATIONS,
        "applicationIndex not in range");

    if (_lastStartTimes[applicationIndex] != lastStartTime)  // NOSONAR S6385: index vs length
    {
        _lastStartTimes[applicationIndex] = lastStartTime;   // NOSONAR S6386: array size
        _lastStartTimesDirty = true;
    }
}

void NvsAppsInfo::Sync()
{
    auto& nvs = _context.GetServices().GetNvs();
    nvs.SetNamespace(NAMESPACE);

    SyncFavorites();
    SyncNrOfTimesStarted();
    SyncLastStartTimes();

    Assert::IsTrue(Types::ETaskId::System, nvs.CommitAndClose(), "Failed to commit AppsInfo.");
}

void NvsAppsInfo::SyncFavorites()
{
    auto& nvs = _context.GetServices().GetNvs();
    if (_favoritesDirty)
    {
        Assert::IsTrue(
            Types::ETaskId::System, 
            nvs.WriteBlob(
                FAVORITES_KEY,
                reinterpret_cast<uint8_t*>(_favorites.data()), // NOSONAR S6022: std::byte
                sizeof(_favorites.data())),
            "Failed to sync favorites.");
        _favoritesDirty = false;
    }
}

void NvsAppsInfo::SyncNrOfTimesStarted()
{
    auto& nvs = _context.GetServices().GetNvs();
    if (_nrOfTimesStartedDirty)
    {
        Assert::IsTrue(
            Types::ETaskId::System,
            nvs.WriteBlob(
                NR_OF_TIMES_STARTED_KEY,
                reinterpret_cast<uint8_t*>(_nrOfTimesStarted.data()),  // NOSONAR S6022: std::byte
                sizeof(_nrOfTimesStarted.data())),
            "Failed to sync NrOfTimesStarted.");
        _nrOfTimesStartedDirty = false;
    }
}

void NvsAppsInfo::SyncLastStartTimes()
{
    auto& nvs = _context.GetServices().GetNvs();
    if (_lastStartTimesDirty)
    {
        Assert::IsTrue(
            Types::ETaskId::System,
            nvs.WriteBlob(
                LAST_START_TIMES_KEY,
                reinterpret_cast<uint8_t*>(_lastStartTimes.data()),   // NOSONAR: std::byte
                sizeof(_lastStartTimes.data())),
            "Failed to sync LastStartTimes.");
        _lastStartTimesDirty = false;
    }
}

