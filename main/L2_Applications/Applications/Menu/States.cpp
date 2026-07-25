#include "States.hpp"
#include "../../../L9_Utils/Math/MathUtils.hpp"
#include "../../../L9_Utils/Debug/Debug.hpp"

using namespace std;

States::States() 
:   _currentState(EState::S000_Welcome), _previousState(EState::S900_SettingInteger),
    _timeInCurrentState(std::chrono::steady_clock::now()),
    _selectedAppTypeIndex(Application::EType::Game), _selectedViewModeIndex(EViewMode::Recent),
    _selectedTagIndex(0), _selectedAppNameIndex(EAppName::OneDPong),
    _selectedHighscoreIndex(0), _swapFavoriteStatus(false), _player1Id(0), _player2Id(0)
{
}

void States::SetStateIf(bool condition, EState newState) 
{
    if (condition)
    {
        _currentState = newState;
    }
}

void States::SetState(EState newState) 
{
    _currentState = newState;
}

States::EAppName States::GetSelectedAppNameIndex() const
{ 
    return _selectedAppNameIndex; 
}

States::EViewMode States::GetSelectedViewModeIndex() const
{ 
    return _selectedViewModeIndex; 
}

uint8_t States::GetSelectedTagIndex() const
{
    return _selectedTagIndex; 
}

Application::EType States::GetSelectedAppTypeIndex() const
{
    return _selectedAppTypeIndex; 
}

uint8_t States::GetSelectedHighscoreIndex() const
{
    return _selectedHighscoreIndex; 
}

bool States::GetSwapFavoriteStatus() const
{
    return _swapFavoriteStatus; 
}

States::EState States::GetCurrentState() const
{
    return _currentState;
}

bool States::OnTimePassed()
{
    bool changed = false;
    auto now = std::chrono::steady_clock::now();
    uint64_t elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(now - _timeInCurrentState).count();

    switch (_currentState)
    {
    case EState::S000_Welcome: 
        if (elapsedMs >= 2000)
        {
            SetState(EState::S010_SelectAppType);
            changed = true;
        }
        break;

    default: /* ignore others */ 
        break;
    }
    return changed;
}

void States::OnSystemButtonPressed()
{
    if (_currentState != EState::S041_AppRunning)
    {
        SetState(EState::S010_SelectAppType);
    }
}

void States::OnJoystickDirectionChanged(JoystickState::EDirection direction)
{
    switch (direction)
    {
    case JoystickState::EDirection::Up: OnJoystickUp(); break;
    case JoystickState::EDirection::Right: OnJoystickRight(); break;
    case JoystickState::EDirection::Down: OnJoystickDown(); break;
    case JoystickState::EDirection::Left: OnJoystickLeft(); break;
    default: break; // Ignore others
    }
}

void States::OnJoystickLeft()
{
    switch (_currentState)
    {
    case EState::S020_SelectViewMode: SetState(EState::S010_SelectAppType); break;
    case EState::S021_SelectTag: 
        _selectedTagIndex = 0;
        SetState(EState::S020_SelectViewMode); 
        break;
    case EState::S030_SelectApp: SetState(EState::S020_SelectViewMode); break;
    case EState::S040_AppStart: SetState(EState::S030_SelectApp); break;
    case EState::S045_AppConfirmQuit: SetState(EState::S044_AppQuit); break;
    case EState::S050_AppSettings: SetState(EState::S030_SelectApp); break;
    case EState::S060_Highscores: SetState(EState::S030_SelectApp); break;
    case EState::S061_HighscoreDetails: SetState(EState::S060_Highscores); break;
    case EState::S070_ResetHighscores: SetState(EState::S030_SelectApp); break;
    case EState::S071_ConfirmHighscoresReset: SetState(EState::S070_ResetHighscores); break;
    case EState::S072_HighscoresResetDone: SetState(EState::S060_Highscores); break;
    case EState::S080_PlayerSetup: SetState(EState::S030_SelectApp); break;
    case EState::S090_SetAsFavorite: SetState(EState::S030_SelectApp); break;
    default: break; // Ignore
    }
}

void States::OnJoystickUp()
{
    int count;
    int tagIndex;

    switch (_currentState)
    {
        case EState::S000_Welcome: SetState(EState::S010_SelectAppType); break;
        case EState::S010_SelectAppType: 
            count = static_cast<int>(Application::EType::Last);
            _selectedAppTypeIndex = MathUtils::WrapEnum(_selectedAppTypeIndex, -1, count);
            break;
        case EState::S020_SelectViewMode:
            count = static_cast<int>(EViewMode::Last);
            _selectedViewModeIndex = MathUtils::WrapEnum(_selectedViewModeIndex, -1, count);
            break;
        case EState::S021_SelectTag: 
            tagIndex = 0;
            switch (_selectedAppTypeIndex) 
            {
            case Application::EType::Game:      tagIndex = static_cast<int>(EGameTag::Last);     break;
            case Application::EType::Demo:      tagIndex = static_cast<int>(EDemoTag::Last);     break;
            case Application::EType::Tool:      tagIndex = static_cast<int>(EUtilityTag::Last);  break;
            case Application::EType::Utility:   tagIndex = static_cast<int>(ESetupAppTag::Last); break;
            default: break;
            }
            _selectedTagIndex = MathUtils::WrapEnum(_selectedTagIndex, -1, tagIndex);
            break;
        case EState::S030_SelectApp:
            _selectedAppNameIndex = MathUtils::WrapEnum(_selectedAppNameIndex, -1, static_cast<int>(EAppName::Last));
            break;
        case EState::S040_AppStart: SetState(EState::S090_SetAsFavorite); break;
        case EState::S043_AppPaused: SetState(EState::S044_AppQuit); break;
        case EState::S044_AppQuit: SetState(EState::S043_AppPaused); break;
        case EState::S050_AppSettings: SetState(EState::S040_AppStart); break;
        case EState::S060_Highscores: SetState(EState::S050_AppSettings); break;
        case EState::S061_HighscoreDetails: 
            _selectedHighscoreIndex = MathUtils::WrapEnum(_selectedHighscoreIndex, -1, _maxHighscoreEntries);
            break;
        case EState::S070_ResetHighscores: SetState(EState::S060_Highscores); break;
        case EState::S072_HighscoresResetDone: SetState(EState::S060_Highscores); break;
        case EState::S080_PlayerSetup: SetState(EState::S070_ResetHighscores); break;
        case EState::S090_SetAsFavorite: 
            SetState((_selectedAppTypeIndex == Application::EType::Game) 
                ? EState::S080_PlayerSetup : EState::S050_AppSettings);
            break;
        default:
            // Ignore all others
            break;
    }
}

void States::OnJoystickDown()
{
    int count;
    int tagIndex;

    switch (_currentState)
    {
    case EState::S000_Welcome: SetState(EState::S010_SelectAppType); break;
    case EState::S010_SelectAppType: 
        count = static_cast<int>(Application::EType::Last);
        _selectedAppTypeIndex = MathUtils::WrapEnum(_selectedAppTypeIndex, 1, count);
        break;
    case EState::S020_SelectViewMode:
        count = static_cast<int>(EViewMode::Last);
        _selectedViewModeIndex = MathUtils::WrapEnum(_selectedViewModeIndex, 1, count);
        break;
    case EState::S021_SelectTag: 
        tagIndex = 0;
        switch (_selectedAppTypeIndex) 
        {
        case Application::EType::Game:        tagIndex = static_cast<int>(EGameTag::Last);     break;
        case Application::EType::Demo:        tagIndex = static_cast<int>(EDemoTag::Last);     break;
        case Application::EType::Tool:      tagIndex = static_cast<int>(EUtilityTag::Last);  break;
        case Application::EType::Utility:   tagIndex = static_cast<int>(ESetupAppTag::Last); break;
        default: break;
        }
        _selectedTagIndex = MathUtils::WrapEnum(_selectedTagIndex, 1, tagIndex);
        break;
    case EState::S030_SelectApp:
        _selectedAppNameIndex = MathUtils::WrapEnum(_selectedAppNameIndex, 1, static_cast<int>(EAppName::Last));
        break;
    case EState::S040_AppStart: SetState(EState::S050_AppSettings); break;
    case EState::S043_AppPaused: SetState(EState::S044_AppQuit); break;
    case EState::S044_AppQuit: SetState(EState::S043_AppPaused); break;
    case EState::S050_AppSettings: 
        SetState((_selectedAppTypeIndex == Application::EType::Game) 
            ? EState::S060_Highscores : EState::S090_SetAsFavorite);
        break;
    case EState::S060_Highscores: SetState(EState::S070_ResetHighscores); break;
    case EState::S061_HighscoreDetails:
        _selectedHighscoreIndex = MathUtils::WrapEnum(_selectedHighscoreIndex, -1, _maxHighscoreEntries);
        break;
    case EState::S070_ResetHighscores: SetState(EState::S080_PlayerSetup); break;
    case EState::S072_HighscoresResetDone: SetState(EState::S060_Highscores); break;
    case EState::S080_PlayerSetup: SetState(EState::S090_SetAsFavorite); break;
    case EState::S090_SetAsFavorite: SetState(EState::S040_AppStart); break;
    default: 
        // Ignore others
        break;
    }
}

void States::OnJoystickRight()
{
    switch (_currentState)
    {
    case EState::S000_Welcome: SetState(EState::S010_SelectAppType); break;
    case EState::S010_SelectAppType: SetState(EState::S020_SelectViewMode); break;
    case EState::S020_SelectViewMode: 
        SetState(_selectedViewModeIndex == EViewMode::Tag ? EState::S021_SelectTag : EState::S030_SelectApp); break;
    case EState::S021_SelectTag: SetState(EState::S030_SelectApp); break;
    case EState::S030_SelectApp: SetState(EState::S040_AppStart); break;
    case EState::S040_AppStart: SetState(EState::S041_AppRunning); break;
    case EState::S043_AppPaused: SetState(EState::S041_AppRunning); break;
    case EState::S044_AppQuit: SetState(EState::S045_AppConfirmQuit); break;
    case EState::S060_Highscores: SetState(EState::S061_HighscoreDetails); break;
    case EState::S070_ResetHighscores: SetState(EState::S071_ConfirmHighscoresReset); break;
    case EState::S072_HighscoresResetDone: SetState(EState::S060_Highscores); break;
    case EState::S090_SetAsFavorite: 
        SetState(EState::S090_SetAsFavorite); // Rerender?
        _swapFavoriteStatus = true;
        break;
    default: break; // Ignore
    }
}

void States::OnJoystickButtonPressed()
{
    switch (_currentState)
    {
    case EState::S010_SelectAppType: SetState(EState::S020_SelectViewMode); break;
    case EState::S020_SelectViewMode: 
        SetState(_selectedViewModeIndex == EViewMode::Tag 
            ? EState::S021_SelectTag : EState::S030_SelectApp); break;
    case EState::S021_SelectTag: SetState(EState::S030_SelectApp); break;
    case EState::S030_SelectApp: SetState(EState::S040_AppStart); break;
    case EState::S040_AppStart: SetState(EState::S041_AppRunning); break;
    case EState::S041_AppRunning: SetState(EState::S043_AppPaused); break;
    case EState::S043_AppPaused: SetState(EState::S041_AppRunning); break;
    case EState::S044_AppQuit: SetState(EState::S045_AppConfirmQuit); break;
    case EState::S045_AppConfirmQuit: SetState(EState::S040_AppStart); break;
    case EState::S060_Highscores: SetState(EState::S061_HighscoreDetails); break;
    case EState::S070_ResetHighscores: SetState(EState::S071_ConfirmHighscoresReset); break;
    case EState::S071_ConfirmHighscoresReset: SetState(EState::S072_HighscoresResetDone); break;
    case EState::S072_HighscoresResetDone: SetState(EState::S060_Highscores); break;
    case EState::S090_SetAsFavorite: 
        SetState(EState::S090_SetAsFavorite); // Rerender?
        _swapFavoriteStatus = true;
        break;
   default: break; // Ignore
    }
}
