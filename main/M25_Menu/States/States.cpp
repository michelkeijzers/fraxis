#include "States.hpp"
#include "../MenuApplication.hpp"
#include "../../M20_Applications/Games/Highscores.hpp"
#include "../../M20_Applications/ApplicationsManager.hpp"
#include "../../M20_Applications/Nvs/NvsSettings.hpp"
#include "../../M30_Messages/Types.hpp"
#include "../../M80_Services/Random/IRandom.hpp"
#include "../../M90_Utilities/Assert/IAssert.hpp"
#include "../../M90_Utilities/Log/Log.hpp"
#include "../../M90_Utilities/Math/MathUtilities.hpp"
#include "../../M90_Utilities/Time/TimeUtilities.hpp"
#include <algorithm>

using namespace std;

States::States(
    M80::Random::IRandom& random,
    M90::Assert::IAssert &assert,
    M90::Math::IMathUtilities &mathUtilities,
    ApplicationsManager& applicationsManager)
:
    _applicationsManager(applicationsManager),
    _applicationModesStates(*this, applicationsManager),
    _applicationSelectionStates(assert, *this, applicationsManager, random),
    _highscoresStates(*this, applicationsManager),
    _settingsStates(applicationsManager),
    _currentState(EState::S000_Welcome),
    _previousState(EState::S900_SettingInteger),
    _timeInCurrentState(M90::Time::TimeUtilities::GetCurrentTimeInUs()),
    _selectedHighscoreIndex(0),
    _swapFavoriteStatus(false),
    _mathUtilities(mathUtilities)
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
        _timeInCurrentState = M90::Time::TimeUtilities::GetCurrentTimeInUs();
        ExecuteCurrentState();
    }
}

void States::SetState(EState newState)
{
    _currentState = newState;
    _timeInCurrentState = M90::Time::TimeUtilities::GetCurrentTimeInUs();
    ExecuteCurrentState();
}

void States::ExecuteCurrentState()
{
    using enum EState;
    switch (_currentState)
    {
    case S021_SelectTag:
        _applicationSelectionStates.FilterSelectableTags();
        break;

    case S030_SelectApplication:
        _applicationSelectionStates.FilterSelectableApplications();
        break;

    case S040_ApplicationMode:
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
    
    if (std::chrono::microseconds elapsedMsInCurrentState = 
        M90::Time::TimeUtilities::GetUsSince(_timeInCurrentState);
        (_currentState == EState::S000_Welcome) && (elapsedMsInCurrentState >= WELCOME_STATE_TIME))
    {
        SetState(EState::S010_SelectApplicationType);
        changed = true;
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
    using enum Types::EJoystickDirection;
    switch (direction)
    {
    case Up: 
        OnJoystickUp(); 
        break;

    case Right: 
        OnJoystickRight(); 
        break;

    case Down: 
        OnJoystickDown(); 
        break;

    case Left: 
        OnJoystickLeft();
        break;

    default: 
        // Ignore others
        break;
    }
}

void States::OnJoystickLeft()
{
    using enum EState;
    switch (_currentState)
    {
    case S020_SelectViewMode: SetState(S010_SelectApplicationType); break;
    case S021_SelectTag: SetState(S020_SelectViewMode); break;
    case S030_SelectApplication: SetState(S020_SelectViewMode); break;
    case S040_ApplicationMode:
        if (ApplicationModesStates::EApplicationMode selectedApplicationMode =
            _applicationModesStates.GetSelectedApplicationMode(); 
            (selectedApplicationMode != ApplicationModesStates::EApplicationMode::Resume) &&
            (selectedApplicationMode != ApplicationModesStates::EApplicationMode::Quit))
        {
            SetState(S030_SelectApplication); 
            break;
        }
        break;
    default: 
        // Ignore others.
        break;
    }
}

void States::OnJoystickUp()
{
    using enum EState;
    switch (_currentState)
    {
    case S000_Welcome: 
        SetState(S010_SelectApplicationType); 
        break;
        
    case S010_SelectApplicationType: 
        _applicationSelectionStates.ModifySelectedApplicationType(false); // decrease
        break;

    case S020_SelectViewMode:
        _applicationSelectionStates.ModifySelectedViewMode(false); // decrease
        break;

    case S021_SelectTag: 
        if (!_applicationSelectionStates.GetSelectableTags().empty())
        {
            const auto count = _applicationSelectionStates.GetSelectableTags().size();
            const auto applicationTypeIndex = static_cast<uint8_t>(
                (_applicationSelectionStates.GetSelectedTagIndex() - 1 + count) % count);
            _applicationSelectionStates.SetSelectedTagIndex(applicationTypeIndex);

        }
        break;

    case S030_SelectApplication:
        _applicationSelectionStates.SetSelectedApplicationIndex(
            static_cast<uint16_t>(_mathUtilities.Clamp(
                _applicationSelectionStates.GetSelectedApplicationIndex() - 1, 
                0, 
                static_cast<int>(
                    _applicationSelectionStates.GetSelectableApplicationIndices().size()) - 1)));
        break;

    case S040_ApplicationMode: 
        _applicationModesStates.OnJoystickUp();
        break;

    default:
        // Ignore all others
        break;
    }
}

void States::OnJoystickDown()
{
    using enum EState;
    switch (_currentState)
    {
    case S000_Welcome: 
        SetState(S010_SelectApplicationType); 
        break;

    case S010_SelectApplicationType: 
        _applicationSelectionStates.ModifySelectedApplicationType(true); // increase
        break;

    case S020_SelectViewMode:
        _applicationSelectionStates.ModifySelectedViewMode(true); // increase
        break;

    case EState::S021_SelectTag: 
        if (!_applicationSelectionStates.GetSelectableTags().empty())
        {
            const auto count = _applicationSelectionStates.GetSelectableTags().size();
            const auto applicationTypeIndex = static_cast<uint8_t>(
                (_applicationSelectionStates.GetSelectedTagIndex() + 1 + count) % count);
            _applicationSelectionStates.SetSelectedTagIndex(applicationTypeIndex);
        }
        break;

    case S030_SelectApplication:
        _applicationSelectionStates.SetSelectedApplicationIndex(
            static_cast<uint16_t>(_mathUtilities.Clamp(
                _applicationSelectionStates.GetSelectedApplicationIndex() + 1, 
                0, 
                static_cast<int>(
                    _applicationSelectionStates.GetSelectableApplicationIndices().size()) - 1)));
        break;

    case S040_ApplicationMode:
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
    using enum EState;
    switch (_currentState)
    {
    case S000_Welcome:
        SetState(S010_SelectApplicationType);
        break;

    case S010_SelectApplicationType:
        SetState(S020_SelectViewMode); 
        break;

    case S020_SelectViewMode: 
        SetState(_applicationSelectionStates.GetSelectedViewMode() == 
            ApplicationSelectionStates::EViewMode::Tag
            ? EState::S021_SelectTag 
            : EState::S030_SelectApplication);
        break;

    case S021_SelectTag:
        if (!_applicationSelectionStates.GetSelectableTags().empty())
        {
            SetState(S030_SelectApplication);
        }
        break;

    case S030_SelectApplication: 
        if (!_applicationSelectionStates.GetSelectableApplicationIndices().empty())
        {
            SetState(S040_ApplicationMode);
        }
        break;

    case S040_ApplicationMode: 
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
