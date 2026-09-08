#pragma once

#include "../Application.hpp"
#include "../../IoStates/JoystickState.hpp"
#include "../../../L3_Messages/Types.hpp"
#include <cstdint>
#include <chrono>
#include <vector>

class ApplicationsManager;
class Random;

class States {
public:
    enum class EState {
        S000_Welcome = 0,
        S010_SelectAppType = 10,
        S020_SelectViewMode = 20,
        S021_SelectTag = 21,
        S030_SelectApp = 30,
        S040_AppStart = 40,
        S041_AppRunning = 41,
        S043_AppPaused = 43,
        S044_AppQuit = 44,
        S045_AppConfirmQuit = 45,
        S050_AppSettings = 50,
        S051_SettingDetails = 51,
        S060_Highscores = 60,
        S061_HighscoreDetails = 61,
        S070_ResetHighscores = 70,
        S071_ConfirmHighscoresReset = 71,
        S072_HighscoresResetDone = 72,
        S080_PlayerSetup = 80,
        S081_PlayerDetails = 81,
        S082_PlayerNew = 82,
        S083_PlayerEdit = 83,
        S090_SetAsFavorite = 90,
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

    explicit States(
        Random& random,
        ApplicationsManager& applicationsManager);
    ~States() = default;

    uint16_t GetSelectedAppIndex() const;
    EViewMode GetSelectedViewModeIndex() const;
    uint8_t GetSelectedTagIndex() const;
    Application::EType GetSelectedAppTypeIndex() const;
    uint8_t GetSelectedHighscoreIndex() const;
    bool GetSwapFavoriteStatus() const;

    EState GetCurrentState() const;

    std::vector<Application::ETag> GetSelectableTags() const;
    std::vector<Application*> GetSelectableApplications() const;
    void SortSelectableApplications();

    bool OnTimePassed();
    void OnSystemButtonPressed();
    void OnJoystickDirectionChanged(
        Types::EJoystickDirection direction);
    void OnJoystickUp();
    void OnJoystickRight();
    void OnJoystickDown();
    void OnJoystickLeft();
    void OnJoystickButtonPressed();
    
private:
    static constexpr uint8_t _MAX_HIGH_SCORES_ENTRIES = 10;

    Random& _random;
    ApplicationsManager& _applicationsManager;

    EState _currentState;
    EState _previousState;
    uint64_t _timeInCurrentState;

    Application::EType _selectedAppTypeIndex;
    EViewMode _selectedViewModeIndex;
    uint8_t _selectedTagIndex;
    int16_t _selectedAppIndex;

    /// @details although std::set is a better type functionally, it can cause heap fragmentation.
    std::vector<Application::ETag> _selectableTags;
    std::vector<Application*> _selectableApplications;

    uint8_t _selectedHighscoreIndex;

    bool _swapFavoriteStatus;

    void SetStateIf(
        bool condition, 
        EState newState);

    void SetState(
        EState newState);

    void ExecuteCurrentState();
    void FilterSelectableTags();
    void FilterSelectableApplications();
    
    void FilterTag(
        IApplication::ETag tag);
};
