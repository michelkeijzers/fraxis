#pragma once

#include "../Components/PinIo.hpp"
#include <chrono>

enum class State {
    S_INIT = -1, 
    S000_WELCOME = 0, 
    S010_SELECT_APP_TYPE = 10, 
    S020_SELECT_VIEW_MODE = 20, 
    S021_SELECT_TAG = 21,
    S030_SELECT_APP = 30, 
    S040_APP_START = 40, 
    S041_APP_RUNNING = 41, 
    S043_APP_PAUSED = 43, 
    S044_APP_QUIT = 44, 
    S045_APP_CONFIRM_QUIT = 45,
    S050_APP_SETTINGS = 50, 
    S051_SETTING_DETAILS = 51, 
    S060_HIGHSCORES = 60, 
    S061_HIGHSCORE_DETAILS = 61, 
    S070_RESET_HIGHSCORES = 70, 
    S071_CONFIRM_HIGHSCORES_RESET = 71, 
    S072_HIGHSCORES_RESET_DONE = 72,
    S080_PLAYER_SETUP = 80, 
    S081_PLAYER_DETAILS = 81, 
    S082_PLAYER_NEW = 82, 
    S083_PLAYER_EDIT = 83, 
    S090_SET_AS_FAVORITE = 90, 
    S900_SETTING_INTEGER = 900, 
    S902_SETTING_ENUM = 902, 
    S903_ENTER_PLAYER_ID = 903
};

class MenuStates {
public:
    enum class EAppType {
        GAME,
        DEMO,
        UTILITY,
        SETUP_APP,
        LAST
    };

    enum class EViewMode {
        RECENT,
        MOST_USED,
        FAVORITES,
        ALPHABETIC,
        TAG,
        NEW,
        RANDOM,
        LAST
    };

    enum class EGameTag {
        ARCADE,
        AUDIO,
        CONTINUOUS,
        HORIZONTAL,
        MICROPHONE,
        PUZZLE, 
        RACING, 
        SHOOTER, 
        SINGLE_PLAYER, 
        TURN_BASED,
        TWO_PLAYER, 
        VERTICAL,
        LAST
    };
        
    enum class EDemoTag 
    {
        AUDIO,
        INTERACTIVE,
        STATIC,
        LAST
    };

    enum class EUtilityTag
    {
        AUDIO,
        CLOCK,
        LED_STRIPS,
        MICROPHONE,
        SPEAKER,
        LAST
    };

    enum class ESetupAppTag
    {
        AUDIO,
        CLOCK,
        DIAGNOSTICS,
        DISPLAYS,
        HARDWARE_TEST,
        JOYSTICKS,
        LEDS,
        LED_STRIPS,
        MICROPHONE,
        SPEAKER,
        SYSTEM_BUTTON,
        INFO,
        LAST
    };

    enum class EAppName {
        ONE_D_PONG,
        LINE_RACER,
        LAST
    };

    State _currentState;
    State _previousState;
    std::chrono::steady_clock::time_point _timeInCurrentState;

    EAppType _selectedAppTypeIndex;
    EViewMode _selectedViewModeIndex;
    uint8_t _selectedTagIndex;
    EAppName _selectedAppNameIndex;

    uint8_t _selectedHighscoreIndex;
    const uint8_t _maxHighscoreEntries = 10;

    bool _swapFavoriteStatus;

    uint8_t _player1Id;
    uint8_t _player2Id;
    
    MenuStates();
    void Update(PinIo::EInput in);

    EAppName GetSelectedAppNameIndex() const;
    EViewMode GetSelectedViewModeIndex() const;
    uint8_t GetSelectedTagIndex() const;
    EAppType GetSelectedAppTypeIndex() const;
    uint8_t GetSelectedHighscoreIndex() const;
    bool GetSwapFavoriteStatus() const;

private:
    void SetStateIf(bool condition, State newState);
    void SetState(State newState);

    bool IsSystemButton(PinIo::EInput in);
    bool IsButton(PinIo::EInput in);
    bool IsRightOrButton(PinIo::EInput in);
    bool IsUp(PinIo::EInput in);
    bool IsDown(PinIo::EInput in);
    bool IsLeft(PinIo::EInput in);
    bool IsRight(PinIo::EInput in);
    bool IsAny(PinIo::EInput in);
};
