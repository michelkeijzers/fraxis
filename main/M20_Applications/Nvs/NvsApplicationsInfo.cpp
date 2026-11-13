#include "NvsApplicationsInfo.hpp"
#include "../ApplicationsManager.hpp"
#include "../../M10_Composition/Context/Context.hpp"
#include "../../M25_Menu/MenuApplication.hpp"
#include "../../M80_Services/Nvs/Nvs.hpp"
#include "../../M90_Utilities/Assert/Assert.hpp"
#include "../../M90_Utilities/Log/Log.hpp"

const std::string NvsApplicationsInfo::NAMESPACE = "apps_info";

const std::string NvsApplicationsInfo::FAVORITES_KEY = "favorites";
const std::string NvsApplicationsInfo::NUMBER_OF_TIMES_STARTED_KEY = "nr_of_times_sta";
const std::string NvsApplicationsInfo::LAST_START_TIMES_KEY = "last_start_tims";


NvsApplicationsInfo::NvsApplicationsInfo(    
    Context& context)
:
    _context(context),
    _favorites(),
    _numberOfTimesStarted(),
    _lastStartTimes(),
    _favoritesDirty(false),
    _numberOfTimesStartedDirty(false),
    _lastStartTimesDirty(false)
{
}

void NvsApplicationsInfo::Read()
{
    auto& nvs = _context.GetServices().GetNvs();
    nvs.SetNamespace(NAMESPACE);
    ReadFavorites();
    ReadNumberOfTimesStarted();
    ReadLastStartTimes();
    nvs.Close();
}

/// @brief Reads the favorites. If there is a size mismatch, write all values.
void NvsApplicationsInfo::ReadFavorites()
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
        M90::Assert::Assert::Equals(
            Types::ETaskId::System, 
            nvs.WriteBlob(
                FAVORITES_KEY, 
                reinterpret_cast<uint8_t*>(_favorites.data()), // NOSONAR: std::byte
                size),
            ESP_OK,
            "Failed to write favorites.");
    }

    _favoritesDirty = false;
}

/// @brief Reads the number of times the application has been started. If there is a size mismatch,
/// write all values.
void NvsApplicationsInfo::ReadNumberOfTimesStarted()
{
    auto& nvs = _context.GetServices().GetNvs();
    if (size_t size = sizeof(_numberOfTimesStarted); nvs.ReadBlob(
        NUMBER_OF_TIMES_STARTED_KEY,
        reinterpret_cast<uint8_t*>(_numberOfTimesStarted.data()), // NOSONAR: std::byte
        size))
    {
        // No action needed.
    }
    else
    {
        M90::Assert::Assert::Equals(
            Types::ETaskId::System,
            nvs.WriteBlob(
                NUMBER_OF_TIMES_STARTED_KEY,
                reinterpret_cast<uint8_t*>(_numberOfTimesStarted.data()), // NOSONAR: std::byte
                size),
            ESP_OK,
            "Failed to write NumberOfTimesStarted.");
    }

    _numberOfTimesStartedDirty = false;
}

/// @brief Reads the last start times of the applications. If there is a size mismatch, write all 
/// values.
void NvsApplicationsInfo::ReadLastStartTimes()
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
        M90::Assert::Assert::Equals(
            Types::ETaskId::System,
            nvs.WriteBlob(
                LAST_START_TIMES_KEY,
                reinterpret_cast<uint8_t*>(_lastStartTimes.data()), // NOSONAR S9545: std::byte
                size),
            ESP_OK,
            "Failed to write LastStartTimes.");
    }

    
    _lastStartTimesDirty = false;
}

bool NvsApplicationsInfo::GetFavorite(
    uint16_t applicationIndex) const
{
    M90::Assert::Assert::IsTrue(
        Types::ETaskId::System, 
        applicationIndex < ApplicationsInfo::NUMBER_OF_APPLICATIONS,
        "applicationIndex not in range");
    return _favorites[applicationIndex]; // NOSONAR S6385: overflowing indes
}

void NvsApplicationsInfo::SetFavorite(
    uint16_t applicationIndex,
    bool favorite)
{
    M90::Assert::Assert::IsTrue(
        Types::ETaskId::System,
        applicationIndex < ApplicationsInfo::NUMBER_OF_APPLICATIONS,
        "applicationIndex not in range");
    if (_favorites[applicationIndex] != favorite) // NOSONAR S6385 index vs length
    {
        _favorites[applicationIndex] = favorite; // NOSONAR S686 array overrun
        _favoritesDirty = true;
    }
}

uint16_t NvsApplicationsInfo::GetNumberOfTimesStarted(
    uint16_t applicationIndex) const
{
    M90::Assert::Assert::IsTrue(
        Types::ETaskId::System,
        applicationIndex < ApplicationsInfo::NUMBER_OF_APPLICATIONS,
        "applicationIndex not in range"); // NOSONAR C28020 expr not true
    return _numberOfTimesStarted[applicationIndex]; // NOSONAR S6385 index vs length
}

void NvsApplicationsInfo::IncreaseNumberOfTimesStarted(
    uint16_t applicationIndex)
{
    M90::Assert::Assert::IsTrue(
        Types::ETaskId::System,
        applicationIndex < ApplicationsInfo::NUMBER_OF_APPLICATIONS,
        "applicationIndex not in range"); // NOSONAR C28020 expr not true
    if (_numberOfTimesStarted[applicationIndex] < UINT16_MAX) // NOSONAR S6385 index vs length
    {
        _numberOfTimesStarted[applicationIndex]++;
        _numberOfTimesStartedDirty = true;
    }
}

uint32_t NvsApplicationsInfo::GetLastStartTime(
    uint16_t applicationIndex) const
{
    M90::Assert::Assert::IsTrue(
        Types::ETaskId::System,
        applicationIndex < ApplicationsInfo::NUMBER_OF_APPLICATIONS,
        "applicationIndex not in range"); // NOSONAR C28020 expr not true

    return _lastStartTimes[applicationIndex]; // NOSONAR S6385 index vs length
}

void NvsApplicationsInfo::SetLastStartTime(
    uint16_t applicationIndex,
    uint32_t lastStartTime)
{
    M90::Assert::Assert::IsTrue(
        Types::ETaskId::System,
        applicationIndex < ApplicationsInfo::NUMBER_OF_APPLICATIONS,
        "applicationIndex not in range");

    if (_lastStartTimes[applicationIndex] != lastStartTime)  // NOSONAR S6385: index vs length
    {
        _lastStartTimes[applicationIndex] = lastStartTime;   // NOSONAR S6386: array size
        _lastStartTimesDirty = true;
    }
}

void NvsApplicationsInfo::Sync()
{
    auto& nvs = _context.GetServices().GetNvs();
    nvs.SetNamespace(NAMESPACE);

    SyncFavorites();
    SyncNumberOfTimesStarted();
    SyncLastStartTimes();

    M90::Assert::Assert::Equals(
        Types::ETaskId::System, 
        nvs.CommitAndClose(), 
        ESP_OK,
        "Failed to commit ApplicationsInfo.");
}

void NvsApplicationsInfo::SyncFavorites()
{
    auto& nvs = _context.GetServices().GetNvs();
    if (_favoritesDirty)
    {
        M90::Assert::Assert::Equals(
            Types::ETaskId::System, 
            nvs.WriteBlob(
                FAVORITES_KEY,
                reinterpret_cast<uint8_t*>(_favorites.data()), // NOSONAR S6022: std::byte
                sizeof(_favorites.data())),
            ESP_OK,
            "Failed to sync favorites.");
        _favoritesDirty = false;
    }
}

void NvsApplicationsInfo::SyncNumberOfTimesStarted()
{
    auto& nvs = _context.GetServices().GetNvs();
    if (_numberOfTimesStartedDirty)
    {
        M90::Assert::Assert::Equals(
            Types::ETaskId::System,
            nvs.WriteBlob(
                NUMBER_OF_TIMES_STARTED_KEY,
                reinterpret_cast<uint8_t*>(_numberOfTimesStarted.data()), // NOSONAR S6022: std::byte
                sizeof(_numberOfTimesStarted.data())),
            ESP_OK,
            "Failed to sync NumberOfTimesStarted.");
        _numberOfTimesStartedDirty = false;
    }
}

void NvsApplicationsInfo::SyncLastStartTimes()
{
    auto& nvs = _context.GetServices().GetNvs();
    if (_lastStartTimesDirty)
    {
        M90::Assert::Assert::Equals(
            Types::ETaskId::System,
            nvs.WriteBlob(
                LAST_START_TIMES_KEY,
                reinterpret_cast<uint8_t*>(_lastStartTimes.data()),   // NOSONAR: std::byte
                sizeof(_lastStartTimes.data())),
            ESP_OK,
            "Failed to sync LastStartTimes.");
        _lastStartTimesDirty = false;
    }
}
