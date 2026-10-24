#pragma once

#include "../Applications/Application.hpp"
#include "../IoStates/JoystickState.hpp"
#include "../../M30_Messages/Types.hpp"
#include <cstdint>
#include <chrono>
#include <vector>

class ApplicationsManager;
class Random;

class States {
private:
    const std::chrono::microseconds WELCOME_STATE_TIME = std::chrono::microseconds(2'000'000);
    const std::chrono::microseconds NVS_SYNC_TIME = std::chrono::microseconds(10'000'000);

public:
    enum class EState {
        S000_Welcome = 0,
        S010_SelectApplicationType = 10,
        S020_SelectViewMode = 20,
        S021_SelectTag = 21,
        S030_SelectApplication = 30,
        S040_ApplicationMode = 40,
        S050_Highscores = 50,
        S900_SettingInteger = 900,
        S902_SettingEnum = 902,
        S903_EnterPlayerId = 903
    };

    enum class EViewMode {
        Recent,
        MostUsed,
        Favorites,
        Alphabetic,
        Tag,
        New,
        Random,
        Last
    };

    static constexpr uint8_t NR_OF_VIEW_MODES = static_cast<uint8_t>(EViewMode::Last);

    enum class EApplicationMode
    {
        Start,
        Running,
        Resume,
        Quit,
        Settings,
        Highscores,
        MakeFavorite,
        ResetSettings,
        ResetHighscores,
        ResetNrOfTimesStarted,
        ResetLastStartTime,
        Last
    };

    static constexpr uint8_t NR_OF_APPLICATION_MODES = static_cast<uint8_t>(EApplicationMode::Last);

    explicit States(
        Random& random,
        ApplicationsManager& applicationsManager);
    ~States() = default;

    uint16_t GetSelectedApplicationIndex() const;
    void SetSelectedApplicationIndex(
        uint16_t selectedApplicationIndex);

    EViewMode GetSelectedViewMode() const;
    void SetSelectedViewMode(
        EViewMode selectedViewMode);

    uint8_t GetSelectedTagIndex() const;
    void SetSelectedTagIndex(
        uint8_t selectedTagIndex);

    Application::EType GetSelectedApplicationType() const;
    void SetSelectedApplicationType(
        Application::EType selectedApplicationType);
        
    EApplicationMode GetSelectedApplicationMode() const;
    uint8_t GetSelectedHighscoreIndex() const;
    bool GetSwapFavoriteStatus() const;

    EState GetCurrentState() const;

    std::vector<Application::ETag> GetSelectableTags() const;
    std::vector<States::EApplicationMode> GetSelectableApplicationModes() const;
    std::vector<uint16_t> GetSelectableApplicationIndices() const;
    void SortSelectableApplications();

    bool OnTimePassed();
    void OnSystemButtonPressed();
    void OnJoystickDirectionChanged(
        Types::EJoystickDirection direction);
    void OnJoystickUp();
    void OnJoystickUpS040_ApplicationMode();
    void OnJoystickRight();
    void OnJoystickDown();
    void OnJoystickDownS040_ApplicationMode();
    void OnJoystickLeft();
    void OnJoystickButtonPressed();
    
private:
    static constexpr uint8_t _MAX_HIGH_SCORES_ENTRIES = 10;

    Random& _random;
    ApplicationsManager& _applicationsManager;

    EState _currentState;
    EState _previousState;
    std::chrono::microseconds _timeInCurrentState;
    std::chrono::microseconds _timeSinceNvsSync;

    /// @details although std::set is a better type functionally, it can cause heap fragmentation.
    std::vector<Application::ETag> _selectableTags;
    std::vector<uint16_t> _selectableApplicationIndices;
    std::vector<EApplicationMode> _selectableApplicationModes;

    EApplicationMode _selectedApplicationMode;
    uint8_t _selectedHighscoreIndex;

    bool _swapFavoriteStatus;

    void SetStateIf(
        bool condition, 
        EState newState);

    void SetState(
        EState newState);

    void ExecuteCurrentState();
    void FilterSelectableTags();
    void FilterSelectableApplicationModes();
    void FilterSelectableApplications();
    
    void FilterTag(
        IApplication::ETag tag);

    void ProcessApplicationMode();
};
