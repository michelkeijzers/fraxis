#include "MenuStates.hpp"
#include "../SharedUtils/MathUtils.hpp"
#include <chrono>
#include <iostream>
using namespace std;

MenuStates::MenuStates() 
    : _currentState(State::S000_WELCOME), _previousState(State::S900_SETTING_INTEGER),
      _timeInCurrentState(std::chrono::steady_clock::now()),
      _selectedAppTypeIndex(EAppType::GAME), _selectedViewModeIndex(EViewMode::RECENT),
      _selectedTagIndex(0), _selectedAppNameIndex(EAppName::ONE_D_PONG),
      _selectedHighscoreIndex(0), _swapFavoriteStatus(false), _player1Id(0), _player2Id(0)
    {}

void MenuStates::Update(EInput in) {
    auto stateAtUpdateStart = _currentState;
    _swapFavoriteStatus = false;

    // Global transition: ANY → S010 via System Button (except S041)
    if (in == EInput::SYSTEM_BUTTON && _currentState != State::S041_APP_RUNNING) {
        _currentState = State::S010_SELECT_APP_TYPE;
        return;
    }

    switch (_currentState) {
    case State::S000_WELCOME:
        SetStateIf(IsAny(in), State::S010_SELECT_APP_TYPE);

        {
            auto now = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - _timeInCurrentState).count();
            if (elapsed >= 2) {
                _currentState = State::S010_SELECT_APP_TYPE;
            }
        }
        break;

    case State::S010_SELECT_APP_TYPE: {
        const int count = static_cast<int>(EAppType::LAST);

        SetStateIf(IsRightOrButton(in), State::S020_SELECT_VIEW_MODE);

        if (IsUp(in) || IsDown(in))
        {
            int delta = (IsUp(in) ? -1 : +1);
            _selectedAppTypeIndex = MathUtils::WrapEnum(_selectedAppTypeIndex, delta, count);
        }
        break;
    }


    case State::S020_SELECT_VIEW_MODE:
        SetStateIf(IsLeft(in), State::S010_SELECT_APP_TYPE);
        if (IsUp(in) || IsDown(in)) {
            int delta = (IsUp(in) ? -1 : +1);
            _selectedViewModeIndex = MathUtils::WrapEnum(_selectedViewModeIndex, delta, static_cast<int>(EViewMode::LAST));
        }
        if (IsRight(in) || IsButton(in)) 
        {
            _currentState = (_selectedViewModeIndex == EViewMode::TAG) ? State::S021_SELECT_TAG : State::S030_SELECT_APP;
        }
        break;

    case State::S021_SELECT_TAG:
        if (IsLeft(in))
        {
            _selectedTagIndex = 0;
            _currentState = State::S020_SELECT_VIEW_MODE;
        }
        if (IsUp(in) || IsDown(in)) 
        {
            int delta = (IsUp(in) ? -1 : +1);
            switch (_selectedAppTypeIndex) {
                case EAppType::GAME:
                    _selectedTagIndex = MathUtils::WrapEnum(_selectedTagIndex, delta, static_cast<int>(EGameTag::LAST));
                    break;
                case EAppType::DEMO:
                    _selectedTagIndex = MathUtils::WrapEnum(_selectedTagIndex, delta, static_cast<int>(EDemoTag::LAST));
                    break;
                case EAppType::UTILITY:
                    _selectedTagIndex = MathUtils::WrapEnum(_selectedTagIndex, delta, static_cast<int>(EUtilityTag::LAST));
                    break;
                case EAppType::SETUP_APP:
                    _selectedTagIndex = MathUtils::WrapEnum(_selectedTagIndex, delta, static_cast<int>(ESetupAppTag::LAST));
                    break;
                default:
                    break;
            }
        }
        if (IsRight(in) || IsButton(in))
        {
            _currentState = State::S030_SELECT_APP;
        }
        break;

    case State::S030_SELECT_APP:
        SetStateIf(IsLeft(in), State::S020_SELECT_VIEW_MODE);
        if (IsUp(in) || IsDown(in))
        {
            int delta = (IsUp(in) ? -1 : +1);
            _selectedAppNameIndex = MathUtils::WrapEnum(_selectedAppNameIndex, delta, static_cast<int>(EAppName::LAST));
            //forceRender = true;
        }
        if (IsRight(in) || IsButton(in))
            _currentState = State::S040_APP_START;
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
        _selectedAppTypeIndex == EAppType::GAME ? State::S060_HIGHSCORES : State::S090_SET_AS_FAVORITE);
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
            _selectedHighscoreIndex = MathUtils::WrapEnum(_selectedHighscoreIndex, delta, _maxHighscoreEntries);
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
        _selectedAppTypeIndex == EAppType::GAME ? State::S080_PLAYER_SETUP : State::S050_APP_SETTINGS);
        if (IsRightOrButton(in)) 
        {
            SetState(State::S090_SET_AS_FAVORITE); // APP STATE FAVORITE
            _swapFavoriteStatus = true;
            //forceRender = true;
        }
        break;

    default:
        break;
    }

    _previousState = stateAtUpdateStart;
}


void MenuStates::SetStateIf(bool condition, State newState) 
{
    if (condition)
    {
        _currentState = newState;
    }
}

void MenuStates::SetState(State newState) 
{
    _currentState = newState;
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


MenuStates::EAppName MenuStates::GetSelectedAppNameIndex() const
{ 
    return _selectedAppNameIndex; 
}

MenuStates::EViewMode MenuStates::GetSelectedViewModeIndex() const
{ 
    return _selectedViewModeIndex; 
}

uint8_t MenuStates::GetSelectedTagIndex() const
{
    return _selectedTagIndex; 
}

MenuStates::EAppType MenuStates::GetSelectedAppTypeIndex() const
{
    return _selectedAppTypeIndex; 
}

uint8_t MenuStates::GetSelectedHighscoreIndex() const
{
    return _selectedHighscoreIndex; 
}

bool MenuStates::GetSwapFavoriteStatus() const
{
    return _swapFavoriteStatus; 
}
