#pragma once

#include "../Applications/IApplication.hpp"
#include "../Applications/ApplicationIds.hpp"
#include <string>
#include <array>

class Context;
class MenuApplication;
class ApplicationsManager;

class NvsAppsInfo
{
public:
    static const std::string NAMESPACE;
    
    static const std::string FAVORITES_KEY;
    static const std::string NR_OF_TIMES_STARTED_KEY;
    static const std::string LAST_START_TIMES_KEY;

    NvsAppsInfo(
        Context& context,
        ApplicationsManager& applicationsManager);
    ~NvsAppsInfo() = default;

    void Read();

    bool GetFavorite(
        uint16_t applicationIndex) const;
    void SetFavorite(
        uint16_t applicationIndex, 
        bool isFavorite);
    
    uint16_t GetNrOfTimesStarted(
        uint16_t applicationIndex) const;
    void IncreaseNrOfTimesStarted(
        uint16_t applicationIndex);

    uint32_t GetLastStartTime(
        uint16_t applicationIndex) const;
    void SetLastStartTime(
        uint16_t applicationIndex, 
        uint32_t lastStartTime);

    void Sync();

private:
    static constexpr uint16_t NR_OF_APPLICATIONS = static_cast<uint16_t>(EApplicationId::Count);

    Context& _context;
    ApplicationsManager& _applicationsManager;

    void ReadFavorites();
    void ReadNrOfTimesStarted();
    void ReadLastStartTimes();

    void SyncFavorites();
    void SyncNrOfTimesStarted();
    void SyncLastStartTimes();

    MenuApplication* GetMenuApplication();

    std::array<bool, NR_OF_APPLICATIONS> _favorites;
    std::array<uint16_t, NR_OF_APPLICATIONS> _nrOfTimesStarted;
    std::array<uint32_t, NR_OF_APPLICATIONS> _lastStartTimes;

    bool _favoritesDirty;
    bool _nrOfTimesStartedDirty;
    bool _lastStartTimesDirty;
};
