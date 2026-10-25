#include "States.hpp"
#include "../MenuApplication.hpp"
#include "../../M20_Applications/Games/Highscores.hpp"
#include "../../M20_Applications/ApplicationsManager.hpp"
#include "../../M20_Applications/Nvs/NvsSettings.hpp"
#include "../../M30_Messages/Types.hpp"
#include "../../M80_Services/Random/Random.hpp"
#include "../../M90_Utilities/Assert/Assert.hpp"
#include "../../M90_Utilities/Log/Log.hpp"
#include "../../M90_Utilities/Math/MathUtilities.hpp"
#include "../../M90_Utilities/Time/TimeUtilities.hpp"
#include <algorithm>
#include <random>

using namespace std;

States::States(
    Random& random,
    ApplicationsManager& applicationsManager)
    :
    _applicationsManager(applicationsManager),
    _applicationModesStates(*this, applicationsManager),
    _applicationSelectionStates(*this, applicationsManager, random),
    _highscoresStates(*this, applicationsManager),
    _settingsStates(*this, applicationsManager),
    _currentState(EState::S000_Welcome),
    _previousState(EState::S900_SettingInteger),
    _timeInCurrentState(TimeUtilities::GetCurrentTimeInUs()),
    _selectedHighscoreIndex(0),
    _swapFavoriteStatus(false)
{
}

ApplicationModesStates& States::GetApplicationModesStates()
{
    return _applicationModesStates;
}

ApplicationSelectionStates& States::GetApplicationSelectionStates()
{
    return _applicationSelectionStates;
}

void States::SetStateIf(bool condition, EState newState)
{
    if (condition)
    {
        _currentState = newState;
        _timeInCurrentState = TimeUtilities::GetCurrentTimeInUs();
        ExecuteCurrentState();
    }
}

void States::SetState(EState newState)
{
    _currentState = newState;
    _timeInCurrentState = TimeUtilities::GetCurrentTimeInUs();
    ExecuteCurrentState();
}

void States::ExecuteCurrentState()
{
    switch (_currentState)
    {
    case EState::S021_SelectTag:
        _applicationSelectionStates.FilterSelectableTags();
        break;

    case EState::S030_SelectApplication:
        _applicationSelectionStates.FilterSelectableApplications();
        break;

    case EState::S040_ApplicationMode:
        _applicationModesStates.ExecuteS040State();
        break;

    default:
        // Ignore others
        break;
    }
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
    std::chrono::microseconds elapsedMsInCurrentState = 
        TimeUtilities::GetUsSince(_timeInCurrentState);

    switch (_currentState)
    {
    case EState::S000_Welcome:
        if (elapsedMsInCurrentState >= WELCOME_STATE_TIME)
        {
            SetState(EState::S010_SelectApplicationType);
            changed = true;
        }
        break;

    default: /* ignore others */
        break;
    }

    _settingsStates.CheckSyncNvsSettings();

    return changed;
}

void States::OnSystemButtonPressed()
{
    switch (_currentState) // NOSONAR: S1301 keep switch instead of if
    {
    case EState::S040_ApplicationMode:
        if (_applicationModesStates.GetSelectedApplicationMode() == 
            ApplicationModesStates::EApplicationMode::Running)
        {
            _applicationsManager.PauseApplication();
            _applicationModesStates.SetSelectedApplicationMode(
                ApplicationModesStates::EApplicationMode::Resume);
        }
        break;

    default:
        SetState(EState::S010_SelectApplicationType); // Return home
        break;
    }
}

void States::OnJoystickDirectionChanged(
    Types::EJoystickDirection direction)
{
    switch (direction)
    {
    case Types::EJoystickDirection::Up: OnJoystickUp(); break;
    case Types::EJoystickDirection::Right: OnJoystickRight(); break;
    case Types::EJoystickDirection::Down: OnJoystickDown(); break;
    case Types::EJoystickDirection::Left: OnJoystickLeft(); break;
    default: 
        // Ignore others
        break;
    }
}

void States::OnJoystickLeft()
{
    switch (_currentState)
    {
    case EState::S020_SelectViewMode: SetState(EState::S010_SelectApplicationType); break;
    case EState::S021_SelectTag: SetState(EState::S020_SelectViewMode); break;
    case EState::S030_SelectApplication: SetState(EState::S020_SelectViewMode); break;
    case EState::S040_ApplicationMode:
        if (ApplicationModesStates::EApplicationMode selectedApplicationMode =
            _applicationModesStates.GetSelectedApplicationMode(); 
            (selectedApplicationMode != ApplicationModesStates::EApplicationMode::Resume) &&
            (selectedApplicationMode != ApplicationModesStates::EApplicationMode::Quit))
        {
            SetState(EState::S030_SelectApplication); break;
        }
        break;
    default: 
        // Ignore others.
        break;
    }
}

void States::OnJoystickUp()
{
    switch (_currentState)
    {
    case EState::S000_Welcome: 
        SetState(EState::S010_SelectApplicationType); 
        break;
        
    case EState::S010_SelectApplicationType: 
        _applicationSelectionStates.SetSelectedApplicationType(false); // decrease
        break;

    case EState::S020_SelectViewMode:
        _applicationSelectionStates.SetSelectedViewMode(false); // decrease
        break;

    case EState::S021_SelectTag: 
        if (!_applicationSelectionStates.GetSelectableTags().empty())
        {
            _applicationSelectionStates.SetSelectedTagIndex(MathUtilities::WrapEnum(
                _applicationSelectionStates.GetSelectedTagIndex(), 
                -1, 
                static_cast<int>(_applicationSelectionStates.GetSelectableTags().size())));
        }
        break;

    case EState::S030_SelectApplication:
        _applicationSelectionStates.SetSelectedApplicationIndex(
            static_cast<uint16_t>(MathUtilities::Clamp(
                _applicationSelectionStates.GetSelectedApplicationIndex() - 1, 
                0, 
                _applicationSelectionStates.GetSelectableApplicationIndices().size() - 1)));
        break;

    case EState::S040_ApplicationMode: 
        _applicationModesStates.OnJoystickUp();
        break;

    default:
        // Ignore all others
        break;
    }
}

void States::OnJoystickDown()
{
    switch (_currentState)
    {
    case EState::S000_Welcome: 
        SetState(EState::S010_SelectApplicationType); 
        break;

    case EState::S010_SelectApplicationType: 
        _applicationSelectionStates.SetSelectedApplicationType(true); // increase
        break;

    case EState::S020_SelectViewMode:
        _applicationSelectionStates.SetSelectedViewMode(true); // increase
        break;

    case EState::S021_SelectTag: 
        if (!_applicationSelectionStates.GetSelectableTags().empty())
        {
            _applicationSelectionStates.SetSelectedTagIndex(MathUtilities::WrapEnum(
                _applicationSelectionStates.GetSelectedTagIndex(), 
                1, 
                static_cast<int>(_applicationSelectionStates.GetSelectableTags().size())));
        }
        break;

    case EState::S030_SelectApplication:
        _applicationSelectionStates.SetSelectedApplicationIndex(
            static_cast<uint16_t>(MathUtilities::Clamp(
                _applicationSelectionStates.GetSelectedApplicationIndex() + 1, 
                0, 
                _applicationSelectionStates.GetSelectableApplicationIndices().size() - 1)));
        break;

    case EState::S040_ApplicationMode:
        _applicationModesStates.OnJoystickDown();
        break;

    default: 
        // Ignore others
        break;
    }
}

void States::OnJoystickRight()
{
    OnJoystickButtonPressed();
}

void States::OnJoystickButtonPressed()
{
    switch (_currentState)
    {
    case EState::S000_Welcome:
        SetState(EState::S010_SelectApplicationType);
        break;

    case EState::S010_SelectApplicationType:
        SetState(EState::S020_SelectViewMode); 
        break;

    case EState::S020_SelectViewMode: 
        SetState(_applicationSelectionStates.GetSelectedViewMode() == 
            ApplicationSelectionStates::EViewMode::Tag
            ? EState::S021_SelectTag 
            : EState::S030_SelectApplication);
        break;

    case EState::S021_SelectTag:
        if (!_applicationSelectionStates.GetSelectableTags().empty())
        {
            SetState(EState::S030_SelectApplication);
        }
        break;

    case EState::S030_SelectApplication: 
        if (!_applicationSelectionStates.GetSelectableApplicationIndices().empty())
        {
            SetState(EState::S040_ApplicationMode);
        }
        break;

    case EState::S040_ApplicationMode: 
        _applicationModesStates.ProcessApplicationMode();
        break;

    default: 
        break; // Ignore
    }
}

void States::StartApplication()
{
    EApplicationId applicationIdToStart = ApplicationsInfo::GetIdByIndex(
        _applicationSelectionStates.GetSelectableApplicationIndices()
        [GetApplicationSelectionStates().GetSelectedApplicationIndex()]);
    _applicationsManager.StartApplication(applicationIdToStart);
}

void States::ResumeApplication()
{
    _applicationsManager.ResumeApplication();
}

void States::StopApplication()
{
    EApplicationId applicationIdToQuit = ApplicationsInfo::GetIdByIndex(
        _applicationSelectionStates.GetSelectableApplicationIndices()
        [_applicationSelectionStates.GetSelectedApplicationIndex()]);
    _applicationsManager.StopApplication(applicationIdToQuit);
}
