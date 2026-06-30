#pragma once

#include "MenuInput.hpp"
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

    State current = State::S000_WELCOME;
    State previousScanState = State::S900_SETTING_INTEGER;
    bool forceRender = false;
    std::chrono::steady_clock::time_point timeInCurrentState;

    EAppType selectedAppTypeIndex = EAppType::GAME;
    EViewMode selectedViewModeIndex = EViewMode::RECENT;
    uint8_t selectedTagIndex;
    EAppName selectedAppNameIndex = EAppName::ONE_D_PONG;

    uint8_t selectedHighscoreIndex = 0;
    const uint8_t maxHighscoreEntries = 10;

    bool swapFavoriteStatus = false;

    uint8_t player1Id = 0;
    uint8_t player2Id = 0;
    
    MenuStates();
    void Update(EInput in);

private:
    void SetStateIf(bool condition, State newState);
    void SetState(State newState);

    bool IsSystemButton(EInput in);
    bool IsButton(EInput in);
    bool IsRightOrButton(EInput in);
    bool IsUp(EInput in);
    bool IsDown(EInput in);
    bool IsLeft(EInput in);
    bool IsRight(EInput in);
    bool IsAny(EInput in);
};
