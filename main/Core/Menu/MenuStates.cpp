#include "MenuStates.hpp"
#include "../SharedUtils/MathUtils.hpp"
#include <chrono>
#include <iostream>
using namespace std;

MenuStates::MenuStates() : timeInCurrentState(std::chrono::steady_clock::now()) {}

void MenuStates::Update(EInput in) {
    auto stateAtUpdateStart = current;
    swapFavoriteStatus = false;

    // Global transition: ANY → S010 via System Button (except S041)
    if (in == EInput::SYSTEM_BUTTON && current != State::S041_APP_RUNNING) {
        current = State::S010_SELECT_APP_TYPE;
        forceRender = true;
        return;
    }
    forceRender = false;

    if (current != previousScanState) 
    {
        cout << "Input: " << static_cast<int>(current) << "\n";
        forceRender = true;
    }

    switch (current) {

    case State::S000_WELCOME:
        SetStateIf(IsAny(in), State::S010_SELECT_APP_TYPE);

        {
            auto now = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - timeInCurrentState).count();
            if (elapsed >= 2) {
                current = State::S010_SELECT_APP_TYPE;
            }
        }
        break;

    case State::S010_SELECT_APP_TYPE: {
        const int count = static_cast<int>(EAppType::LAST);

        SetStateIf(IsRightOrButton(in), State::S020_SELECT_VIEW_MODE);

        if (IsUp(in) || IsDown(in))
        {
            int delta = (IsUp(in) ? -1 : +1);
            selectedAppTypeIndex = MathUtils::WrapEnum(selectedAppTypeIndex, delta, count);
            forceRender = true;
        }
        break;
    }


    case State::S020_SELECT_VIEW_MODE:
        SetStateIf(IsLeft(in), State::S010_SELECT_APP_TYPE);
        if (IsUp(in) || IsDown(in)) {
            int delta = (IsUp(in) ? -1 : +1);
            selectedViewModeIndex = MathUtils::WrapEnum(selectedViewModeIndex, delta, static_cast<int>(EViewMode::LAST));
            forceRender = true;
        }
        if (IsRight(in) || IsButton(in)) {
            if (selectedViewModeIndex == EViewMode::TAG) {
                current = State::S021_SELECT_TAG;
            }
            else {
                current = State::S030_SELECT_APP;
            }
        }
        break;

    case State::S021_SELECT_TAG:
        if (IsLeft(in))
        {
            selectedTagIndex = 0;
            current = State::S020_SELECT_VIEW_MODE;
        }
        if (IsUp(in) || IsDown(in)) 
        {
            int delta = (IsUp(in) ? -1 : +1);
            switch (selectedAppTypeIndex) {
                case EAppType::GAME:
                    selectedTagIndex = MathUtils::WrapEnum(selectedTagIndex, delta, static_cast<int>(EGameTag::LAST));
                    break;
                case EAppType::DEMO:
                    selectedTagIndex = MathUtils::WrapEnum(selectedTagIndex, delta, static_cast<int>(EDemoTag::LAST));
                    break;
                case EAppType::UTILITY:
                    selectedTagIndex = MathUtils::WrapEnum(selectedTagIndex, delta, static_cast<int>(EUtilityTag::LAST));
                    break;
                case EAppType::SETUP_APP:
                    selectedTagIndex = MathUtils::WrapEnum(selectedTagIndex, delta, static_cast<int>(ESetupAppTag::LAST));
                    break;
                default:
                    break;
            }
            forceRender = true;
        }
        if (IsRight(in) || IsButton(in))
        {
            current = State::S030_SELECT_APP;
        }
        break;

    case State::S030_SELECT_APP:
        SetStateIf(IsLeft(in), State::S020_SELECT_VIEW_MODE);
        if (IsUp(in) || IsDown(in))
        {
            int delta = (IsUp(in) ? -1 : +1);
            selectedAppNameIndex = MathUtils::WrapEnum(selectedAppNameIndex, delta, static_cast<int>(EAppName::LAST));
            forceRender = true;
        }
        if (IsRight(in) || IsButton(in))
            current = State::S040_APP_START;
        break;
        
    case State::S040_APP_START:
        SetStateIf(IsLeft(in), State::S030_SELECT_APP);
        SetStateIf(IsUp(in), State::S090_SET_AS_FAVORITE);
        SetStateIf(IsDown(in), State::S050_APP_SETTINGS);
        SetStateIf(IsRightOrButton(in), State::S041_APP_RUNNING);
        break;

    case State::S041_APP_RUNNING:
        SetStateIf(IsSystemButton(in), State::S043_APP_PAUSED);
        break;

    case State::S043_APP_PAUSED:
        SetStateIf(IsUp(in), State::S044_APP_QUIT);
        SetStateIf(IsDown(in), State::S044_APP_QUIT);
        SetStateIf(IsRightOrButton(in), State::S041_APP_RUNNING);
        break;

    case State::S044_APP_QUIT:
        SetStateIf(IsUp(in), State::S043_APP_PAUSED);
        SetStateIf(IsDown(in), State::S043_APP_PAUSED);
        SetStateIf(IsRightOrButton(in), State::S045_APP_CONFIRM_QUIT);
        break;

    case State::S045_APP_CONFIRM_QUIT:
        SetStateIf(IsLeft(in), State::S044_APP_QUIT);
        SetStateIf(IsButton(in), State::S040_APP_START);
        break;

    case State::S050_APP_SETTINGS:
        SetStateIf(IsLeft(in), State::S030_SELECT_APP);
        SetStateIf(IsDown(in), 
         selectedAppTypeIndex == EAppType::GAME ? State::S060_HIGHSCORES : State::S090_SET_AS_FAVORITE);
        SetStateIf(IsUp(in), State::S040_APP_START);
        break;

    case State::S060_HIGHSCORES:
        SetStateIf(IsLeft(in), State::S030_SELECT_APP);
        SetStateIf(IsDown(in), State::S070_RESET_HIGHSCORES);
        SetStateIf(IsUp(in), State::S050_APP_SETTINGS);
        SetStateIf(IsRightOrButton(in), State::S061_HIGHSCORE_DETAILS);
        break;

    case State::S061_HIGHSCORE_DETAILS:
        SetStateIf(IsLeft(in), State::S060_HIGHSCORES);
        if (IsUp(in) || IsDown(in)) 
        {
            int delta = (IsUp(in) ? -1 : +1);
            selectedHighscoreIndex = MathUtils::WrapEnum(selectedHighscoreIndex, delta, maxHighscoreEntries);
            forceRender = true;
        }
        break;

    case State::S070_RESET_HIGHSCORES:
        SetStateIf(IsLeft(in), State::S030_SELECT_APP);
        SetStateIf(IsDown(in), State::S080_PLAYER_SETUP);
        SetStateIf(IsUp(in), State::S060_HIGHSCORES);
        SetStateIf(IsRightOrButton(in), State::S071_CONFIRM_HIGHSCORES_RESET);
        break;

    case State::S071_CONFIRM_HIGHSCORES_RESET:
        SetStateIf(IsLeft(in), State::S070_RESET_HIGHSCORES);
        SetStateIf(IsButton(in), State::S072_HIGHSCORES_RESET_DONE);
        break;

    case State::S072_HIGHSCORES_RESET_DONE:
        SetStateIf(IsAny(in), State::S060_HIGHSCORES);
        break;
    
    case State::S080_PLAYER_SETUP:
        SetStateIf(IsLeft(in), State::S030_SELECT_APP);
        SetStateIf(IsDown(in), State::S090_SET_AS_FAVORITE);
        SetStateIf(IsUp(in), State::S070_RESET_HIGHSCORES); // APP RESET HIGH SCORES
        break;

    case State::S090_SET_AS_FAVORITE:
        SetStateIf(IsLeft(in), State::S030_SELECT_APP);
        SetStateIf(IsDown(in), State::S040_APP_START);
        SetStateIf(IsUp(in), 
         selectedAppTypeIndex == EAppType::GAME ? State::S080_PLAYER_SETUP : State::S050_APP_SETTINGS);
        if (IsRightOrButton(in)) 
        {
            SetState(State::S090_SET_AS_FAVORITE); // APP STATE FAVORITE
            swapFavoriteStatus = true;
            forceRender = true;
        }
        break;

    default:
        break;
    }

    previousScanState = stateAtUpdateStart;
}


void MenuStates::SetStateIf(bool condition, State newState) 
{
    if (condition)
    {
        forceRender |= current != newState;
        current = newState;
    }
}

void MenuStates::SetState(State newState) 
{
    current = newState;
    forceRender |= current != newState;
}

bool MenuStates::IsSystemButton(EInput in) 
{
    return in == EInput::SYSTEM_BUTTON;
}

bool MenuStates::IsButton(EInput in) 
{
    return (in == EInput::P1_BUTTON) || (in == EInput::P2_BUTTON);
}

bool MenuStates::IsRightOrButton(EInput in) 
{
    return IsRight(in) || IsButton(in);
}

bool MenuStates::IsUp(EInput in) 
{
    return (in == EInput::P1_UP) || (in == EInput::P2_UP);
}

bool MenuStates::IsDown(EInput in) 
{
    return (in == EInput::P1_DOWN) || (in == EInput::P2_DOWN);
}

bool MenuStates::IsLeft(EInput in) 
{
    return (in == EInput::P1_LEFT) || (in == EInput::P2_LEFT);
}

bool MenuStates::IsRight(EInput in) 
{
    return (in == EInput::P1_RIGHT) || (in == EInput::P2_RIGHT);
}

bool MenuStates::IsAny(EInput in) 
{
    return in != EInput::NONE;
}
