#include "MenuStates.hpp"
#include <iostream>
#include "../Components/PinIo.hpp"
#include "../../L8_Services/Math/MathUtils.hpp"
#include "../../L8_Services/Debug/Debug.hpp"

using namespace std;

MenuStates::MenuStates() 
:   _currentState(State::S000_WELCOME), _previousState(State::S900_SETTING_INTEGER),
    _timeInCurrentState(std::chrono::steady_clock::now()),
    _selectedAppTypeIndex(EAppType::GAME), _selectedViewModeIndex(EViewMode::RECENT),
    _selectedTagIndex(0), _selectedAppNameIndex(EAppName::ONE_D_PONG),
    _selectedHighscoreIndex(0), _swapFavoriteStatus(false), _player1Id(0), _player2Id(0)
{
}

void MenuStates::Update(std::vector<PinIo::InputEvent> inputEvents)
{
    auto stateAtUpdateStart = _currentState;
    _swapFavoriteStatus = false;
    UpdateForMsPassed();
    for (const auto& inputEvent : inputEvents)
    {
        if (inputEvent.type == PinIo::InputEvent::EType::Pressed)
        {
            UpdateForInputEvent(inputEvent);
        }
    }
    _previousState = stateAtUpdateStart;
}

void MenuStates::UpdateForMsPassed()
{
    auto now = std::chrono::steady_clock::now();
    uint64_t elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(now - _timeInCurrentState).count();

    switch (_currentState)
    {
    case State::S000_WELCOME: UpdateS000ForMsPassed(elapsedMs); break;
    default: /* ignore others */ break;
    }
}

void MenuStates::UpdateS000ForMsPassed(uint64_t elapsedMs)
{
    if (elapsedMs >= 2000)
    {
        _currentState = State::S010_SELECT_APP_TYPE;
    }
}

void MenuStates::UpdateForInputEvent(PinIo::InputEvent inputEvent)
{
    PinIoMappings::EIdBit idBit = inputEvent.idBit;

    // Global transition: ANY → S010 via System Button (except S041)
    if ((idBit == PinIoMappings::EIdBit::SystemButton) && (_currentState != State::S041_APP_RUNNING))
    {
        _currentState = State::S010_SELECT_APP_TYPE;
        return;
    }

    switch (_currentState) {
    case State::S000_WELCOME:                   UpdateS000ForInputEvent(idBit, inputEvent); break;
    case State::S010_SELECT_APP_TYPE:           UpdateS010ForInputEvent(idBit, inputEvent); break;
    case State::S020_SELECT_VIEW_MODE:          UpdateS020ForInputEvent(idBit, inputEvent); break;
    case State::S021_SELECT_TAG:                UpdateS021ForInputEvent(idBit, inputEvent); break;
    case State::S030_SELECT_APP:                UpdateS030ForInputEvent(idBit, inputEvent); break;
    case State::S040_APP_START:                 UpdateS040ForInputEvent(idBit, inputEvent); break;
    case State::S041_APP_RUNNING:               UpdateS041ForInputEvent(idBit, inputEvent); break;
    case State::S043_APP_PAUSED:                UpdateS043ForInputEvent(idBit, inputEvent); break;
    case State::S044_APP_QUIT:                  UpdateS044ForInputEvent(idBit, inputEvent); break;
    case State::S045_APP_CONFIRM_QUIT:          UpdateS045ForInputEvent(idBit, inputEvent); break;
    case State::S050_APP_SETTINGS:              UpdateS050ForInputEvent(idBit, inputEvent); break;
    case State::S060_HIGHSCORES:                UpdateS060ForInputEvent(idBit, inputEvent); break;
    case State::S061_HIGHSCORE_DETAILS:         UpdateS061ForInputEvent(idBit, inputEvent); break;
    case State::S070_RESET_HIGHSCORES:          UpdateS070ForInputEvent(idBit, inputEvent); break;
    case State::S071_CONFIRM_HIGHSCORES_RESET:  UpdateS071ForInputEvent(idBit, inputEvent); break;
    case State::S072_HIGHSCORES_RESET_DONE:     UpdateS072ForInputEvent(idBit, inputEvent); break;
    case State::S080_PLAYER_SETUP:              UpdateS080ForInputEvent(idBit, inputEvent); break;
    case State::S090_SET_AS_FAVORITE:           UpdateS090ForInputEvent(idBit, inputEvent); break;
    default: break;
    }
}

void MenuStates::UpdateS000ForInputEvent(PinIoMappings::EIdBit idBit, PinIo::InputEvent inputEvent)
{
    SetStateIf(IsAny(idBit), State::S010_SELECT_APP_TYPE);
}

void MenuStates::UpdateS010ForInputEvent(PinIoMappings::EIdBit idBit, PinIo::InputEvent inputEvent)
{
    const int count = static_cast<int>(EAppType::LAST);
    SetStateIf(IsRightOrButton(idBit), State::S020_SELECT_VIEW_MODE);

    if (IsUp(idBit) || IsDown(idBit))
    {
        int delta = (IsUp(idBit) ? -1 : +1);
        _selectedAppTypeIndex = MathUtils::WrapEnum(_selectedAppTypeIndex, delta, count);
    }
}

void MenuStates::UpdateS020ForInputEvent(PinIoMappings::EIdBit idBit, PinIo::InputEvent inputEvent)
{
    SetStateIf(IsLeft(idBit), State::S010_SELECT_APP_TYPE);
    if (IsUp(idBit) || IsDown(idBit)) {
        int delta = (IsUp(idBit) ? -1 : +1);
        _selectedViewModeIndex = MathUtils::WrapEnum(_selectedViewModeIndex, delta, static_cast<int>(EViewMode::LAST));
    }
    if (IsRight(idBit) || IsButton(idBit))
    {
        _currentState = (_selectedViewModeIndex == EViewMode::TAG) ? State::S021_SELECT_TAG : State::S030_SELECT_APP;
    }
}

void MenuStates::UpdateS021ForInputEvent(PinIoMappings::EIdBit idBit, PinIo::InputEvent inputEvent)
{
    if (IsLeft(idBit))
    {
        _selectedTagIndex = 0;
        _currentState = State::S020_SELECT_VIEW_MODE;
    }
    if (IsUp(idBit) || IsDown(idBit))
    {
        int delta = (IsUp(idBit) ? -1 : +1);
        int tagIndex = 0;
        switch (_selectedAppTypeIndex) {
        case EAppType::GAME:        tagIndex = static_cast<int>(EGameTag::LAST);     break;
        case EAppType::DEMO:        tagIndex = static_cast<int>(EDemoTag::LAST);     break;
        case EAppType::UTILITY:     tagIndex = static_cast<int>(EUtilityTag::LAST);  break;
        case EAppType::SETUP_APP:   tagIndex = static_cast<int>(ESetupAppTag::LAST); break;
        default: break;
        }
        _selectedTagIndex = MathUtils::WrapEnum(_selectedTagIndex, delta, tagIndex);

    }
    if (IsRight(idBit) || IsButton(idBit))
    {
        _currentState = State::S030_SELECT_APP;
    }

}

void MenuStates::UpdateS030ForInputEvent(PinIoMappings::EIdBit idBit, PinIo::InputEvent inputEvent)
{
    SetStateIf(IsLeft(idBit), State::S020_SELECT_VIEW_MODE);
    if (IsUp(idBit) || IsDown(idBit))
    {
        int delta = (IsUp(idBit) ? -1 : +1);
        _selectedAppNameIndex = MathUtils::WrapEnum(_selectedAppNameIndex, delta, static_cast<int>(EAppName::LAST));
        //forceRender = true;
    }
    if (IsRight(idBit) || IsButton(idBit))
        _currentState = State::S040_APP_START;

}

void MenuStates::UpdateS040ForInputEvent(PinIoMappings::EIdBit idBit, PinIo::InputEvent inputEvent)
{
    SetStateIf(IsLeft(idBit), State::S030_SELECT_APP);
    SetStateIf(IsUp(idBit), State::S090_SET_AS_FAVORITE);
    SetStateIf(IsDown(idBit), State::S050_APP_SETTINGS);
    SetStateIf(IsRightOrButton(idBit), State::S041_APP_RUNNING);

}

void MenuStates::UpdateS041ForInputEvent(PinIoMappings::EIdBit idBit, PinIo::InputEvent inputEvent)
{
    SetStateIf(IsSystemButton(idBit), State::S043_APP_PAUSED);

}

void MenuStates::UpdateS043ForInputEvent(PinIoMappings::EIdBit idBit, PinIo::InputEvent inputEvent)
{
    SetStateIf(IsUp(idBit), State::S044_APP_QUIT);
    SetStateIf(IsDown(idBit), State::S044_APP_QUIT);
    SetStateIf(IsRightOrButton(idBit), State::S041_APP_RUNNING);

}

void MenuStates::UpdateS044ForInputEvent(PinIoMappings::EIdBit idBit, PinIo::InputEvent inputEvent)
{
    SetStateIf(IsUp(idBit), State::S043_APP_PAUSED);
    SetStateIf(IsDown(idBit), State::S043_APP_PAUSED);
    SetStateIf(IsRightOrButton(idBit), State::S045_APP_CONFIRM_QUIT);

}

void MenuStates::UpdateS045ForInputEvent(PinIoMappings::EIdBit idBit, PinIo::InputEvent inputEvent)
{
    SetStateIf(IsLeft(idBit), State::S044_APP_QUIT);
    SetStateIf(IsButton(idBit), State::S040_APP_START);

}

void MenuStates::UpdateS050ForInputEvent(PinIoMappings::EIdBit idBit, PinIo::InputEvent inputEvent)
{
    SetStateIf(IsLeft(idBit), State::S030_SELECT_APP);
    SetStateIf(IsDown(idBit),
        _selectedAppTypeIndex == EAppType::GAME ? State::S060_HIGHSCORES : State::S090_SET_AS_FAVORITE);
    SetStateIf(IsUp(idBit), State::S040_APP_START);

}

void MenuStates::UpdateS060ForInputEvent(PinIoMappings::EIdBit idBit, PinIo::InputEvent inputEvent)
{
    SetStateIf(IsLeft(idBit), State::S030_SELECT_APP);
    SetStateIf(IsDown(idBit), State::S070_RESET_HIGHSCORES);
    SetStateIf(IsUp(idBit), State::S050_APP_SETTINGS);
    SetStateIf(IsRightOrButton(idBit), State::S061_HIGHSCORE_DETAILS);

}

void MenuStates::UpdateS061ForInputEvent(PinIoMappings::EIdBit idBit, PinIo::InputEvent inputEvent)
{
    SetStateIf(IsLeft(idBit), State::S060_HIGHSCORES);
    if (IsUp(idBit) || IsDown(idBit))
    {
        int delta = (IsUp(idBit) ? -1 : +1);
        _selectedHighscoreIndex = MathUtils::WrapEnum(_selectedHighscoreIndex, delta, _maxHighscoreEntries);
    }
}

void MenuStates::UpdateS070ForInputEvent(PinIoMappings::EIdBit idBit, PinIo::InputEvent inputEvent)
{
    SetStateIf(IsLeft(idBit), State::S030_SELECT_APP);
    SetStateIf(IsDown(idBit), State::S080_PLAYER_SETUP);
    SetStateIf(IsUp(idBit), State::S060_HIGHSCORES);
    SetStateIf(IsRightOrButton(idBit), State::S071_CONFIRM_HIGHSCORES_RESET);
}

void MenuStates::UpdateS071ForInputEvent(PinIoMappings::EIdBit idBit, PinIo::InputEvent inputEvent)
{
    SetStateIf(IsLeft(idBit), State::S070_RESET_HIGHSCORES);
    SetStateIf(IsButton(idBit), State::S072_HIGHSCORES_RESET_DONE);

}

void MenuStates::UpdateS072ForInputEvent(PinIoMappings::EIdBit idBit, PinIo::InputEvent inputEvent)
{
    SetStateIf(IsAny(idBit), State::S060_HIGHSCORES);
}

void MenuStates::UpdateS080ForInputEvent(PinIoMappings::EIdBit idBit, PinIo::InputEvent inputEvent)
{
    SetStateIf(IsLeft(idBit), State::S030_SELECT_APP);
    SetStateIf(IsDown(idBit), State::S090_SET_AS_FAVORITE);
    SetStateIf(IsUp(idBit), State::S070_RESET_HIGHSCORES); // APP RESET HIGH SCORES
}

void MenuStates::UpdateS090ForInputEvent(PinIoMappings::EIdBit idBit, PinIo::InputEvent inputEvent)
{
    SetStateIf(IsLeft(idBit), State::S030_SELECT_APP);
    SetStateIf(IsDown(idBit), State::S040_APP_START);
    SetStateIf(IsUp(idBit), _selectedAppTypeIndex == EAppType::GAME 
        ? State::S080_PLAYER_SETUP : State::S050_APP_SETTINGS);
    if (IsRightOrButton(idBit))
    {
        SetState(State::S090_SET_AS_FAVORITE); // APP STATE FAVORITE
        _swapFavoriteStatus = true;
    }

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

bool MenuStates::IsSystemButton(PinIoMappings::EIdBit idBit)
{
    return idBit == PinIoMappings::EIdBit::SystemButton;
}

bool MenuStates::IsButton(PinIoMappings::EIdBit idBit)
{
    return ((idBit == PinIoMappings::EIdBit::Player1Button) || (idBit == PinIoMappings::EIdBit::Player2Button));
}

bool MenuStates::IsRightOrButton(PinIoMappings::EIdBit idBit)
{
    return IsRight(idBit) || IsButton(idBit);
}

bool MenuStates::IsUp(PinIoMappings::EIdBit idBit)
{
    return ((idBit == PinIoMappings::EIdBit::Player1Up) || (idBit == PinIoMappings::EIdBit::Player2Up));
}

bool MenuStates::IsDown(PinIoMappings::EIdBit idBit)
{
    return ((idBit == PinIoMappings::EIdBit::Player1Down) || (idBit == PinIoMappings::EIdBit::Player2Down));
}

bool MenuStates::IsLeft(PinIoMappings::EIdBit idBit)
{
    return ((idBit == PinIoMappings::EIdBit::Player1Left) || (idBit == PinIoMappings::EIdBit::Player2Left));
}

bool MenuStates::IsRight(PinIoMappings::EIdBit idBit)
{
    return ((idBit == PinIoMappings::EIdBit::Player1Right) || (idBit == PinIoMappings::EIdBit::Player2Right));
}

bool MenuStates::IsAny(PinIoMappings::EIdBit idBit)
{
    return true;
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
