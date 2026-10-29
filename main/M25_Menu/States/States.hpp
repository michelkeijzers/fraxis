#pragma once

#include "ApplicationModesStates.hpp"
#include "ApplicationSelectionStates.hpp"
#include "HighscoresStates.hpp"
#include "SettingsStates.hpp"
#include "../../M20_Applications/Applications/Application.hpp"
#include "../../M20_Applications/IoStates/JoystickState.hpp"
#include "../../M30_Messages/Types.hpp"
#include <cstdint>
#include <chrono>
#include <vector>

class ApplicationsManager;
class Random;

class States {
private:
    static constexpr std::chrono::microseconds WELCOME_STATE_TIME = 
        std::chrono::microseconds(2'000'000);

public:
    enum class EState : uint16_t
    {
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

    explicit States(
        Random& random,
        ApplicationsManager& applicationsManager);

    States(const States&) = delete;
    States& operator=(const States&) = delete;
    States(States&&) = delete;
    States& operator=(States&&) = delete;

    ~States() = default;

    [[nodiscard]] ApplicationModesStates& GetApplicationModesStates();
    [[nodiscard]] ApplicationSelectionStates& GetApplicationSelectionStates();
    // [[nodiscard]] HighscoresStates& GetHighscoresStates(); // NOSONAR VCR001 TODO highscores

    [[nodiscard]] EState GetCurrentState() const;

    [[nodiscard]] bool GetSwapFavoriteStatus() const;
    [[nodiscard]] uint8_t GetSelectedHighscoreIndex() const;

    bool OnTimePassed();
    void OnSystemButtonPressed();
    void OnJoystickDirectionChanged(
        Types::EJoystickDirection direction);
    void OnJoystickUp();
    void OnJoystickRight();
    void OnJoystickDown();
    void OnJoystickLeft();
    void OnJoystickButtonPressed();
    
    void StartApplication();
    void ResumeApplication();
    void StopApplication();
    
private:
    static constexpr uint8_t MAX_HIGH_SCORES_ENTRIES = 10;

    ApplicationsManager& _applicationsManager;

    ApplicationModesStates _applicationModesStates;
    ApplicationSelectionStates _applicationSelectionStates;
    HighscoresStates _highscoresStates;
    SettingsStates _settingsStates;

    EState _currentState;
    EState _previousState;
    std::chrono::microseconds _timeInCurrentState;

    /// @details although std::set is a better type functionally, it can cause heap fragmentation.
    uint8_t _selectedHighscoreIndex;

    bool _swapFavoriteStatus;

    void SetStateIf(
        bool condition, 
        EState newState);

    void SetState(
        EState newState);

    void ExecuteCurrentState();
};
