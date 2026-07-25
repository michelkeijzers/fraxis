#pragma once

#include <vector>
#include <cstdint>
#include <chrono>
#include "../../IoStates/JoystickState.hpp"
#include "../Application.hpp"
#include "../../../L4_DomainModels/I2c/IoPins/Joystick.hpp"

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

    enum class EGameTag {
        Arcade,
        Audio,
        Continuous,
        Horizontal,
        Microphone,
        Puzzle, 
        Racing, 
        Shooter, 
        SinglePlayer, 
        TurnBased,
        TwoPlayers, 
        Vertical,
        Last
    };
        
    enum class EDemoTag 
    {
        Audio,
        Interactive,
        Static,
        Last
    };

    enum class EUtilityTag
    {
        Audio,
        Clock,
        LedStrips,
        Microphone,
        Speaker,
        Last
    };

    enum class ESetupAppTag
    {
        Audio,
        Clock,
        Diagnostics,
        Displays,
        HardwareTest,
        Joysticks,
        Leds,
        LedStrips,
        Microphone,
        Speaker,
        SystemButton,
        Info,
        Last
    };

    enum class EAppName {
        OneDPong,
        LineRacer,
        Last
    };

    States();

    EAppName GetSelectedAppNameIndex() const;
    EViewMode GetSelectedViewModeIndex() const;
    uint8_t GetSelectedTagIndex() const;
    Application::EType GetSelectedAppTypeIndex() const;
    uint8_t GetSelectedHighscoreIndex() const;
    bool GetSwapFavoriteStatus() const;

    EState GetCurrentState() const;
    
    bool OnTimePassed();
    void OnSystemButtonPressed();
    void OnJoystickDirectionChanged(Joystick::EDirection direction);
    void OnJoystickUp();
    void OnJoystickRight();
    void OnJoystickDown();
    void OnJoystickLeft();
    void OnJoystickButtonPressed();
    
private:
    EState _currentState;
    EState _previousState;
    std::chrono::steady_clock::time_point _timeInCurrentState;

    Application::EType _selectedAppTypeIndex;
    EViewMode _selectedViewModeIndex;
    uint8_t _selectedTagIndex;
    EAppName _selectedAppNameIndex;

    uint8_t _selectedHighscoreIndex;
    const uint8_t _maxHighscoreEntries = 10;

    bool _swapFavoriteStatus;

    uint8_t _player1Id;
    uint8_t _player2Id;
    
    void SetStateIf(bool condition, EState newState);
    void SetState(EState newState);
};
