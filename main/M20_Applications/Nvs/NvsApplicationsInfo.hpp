#pragma once

#include "../Applications/IApplication.hpp"
#include "../Applications/ApplicationIds.hpp"
#include "../Applications/ApplicationsInfo.hpp"
#include <string>
#include <array>

class Context;
class MenuApplication;
class ApplicationsManager;

class NvsApplicationsInfo
{
public:
    static const std::string NAMESPACE;

    static const std::string FAVORITES_KEY;
    static const std::string NUMBER_OF_TIMES_STARTED_KEY;
    static const std::string LAST_START_TIMES_KEY;

    explicit NvsApplicationsInfo(
        Context& context);
    ~NvsApplicationsInfo() = default;

    void Read();

    bool GetFavorite(
        uint16_t applicationIndex) const;
    void SetFavorite(
        uint16_t applicationIndex, 
        bool isFavorite);
    
    uint16_t GetNumberOfTimesStarted(
        uint16_t applicationIndex) const;
    void IncreaseNumberOfTimesStarted(
        uint16_t applicationIndex);

    uint32_t GetLastStartTime(
        uint16_t applicationIndex) const;
    void SetLastStartTime(
        uint16_t applicationIndex, 
        uint32_t lastStartTime);

    void Sync();

private:
    Context& _context;

    void ReadFavorites();
    void ReadNumberOfTimesStarted();
    void ReadLastStartTimes();

    void SyncFavorites();
    void SyncNumberOfTimesStarted();
    void SyncLastStartTimes();

    std::array<bool, ApplicationsInfo::NUMBER_OF_APPLICATIONS> _favorites;
    std::array<uint16_t, ApplicationsInfo::NUMBER_OF_APPLICATIONS> _numberOfTimesStarted;
    std::array<uint32_t, ApplicationsInfo::NUMBER_OF_APPLICATIONS> _lastStartTimes;

    bool _favoritesDirty;
    bool _numberOfTimesStartedDirty;
    bool _lastStartTimesDirty;
};
