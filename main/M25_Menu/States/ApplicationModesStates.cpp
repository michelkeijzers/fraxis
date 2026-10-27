#include "ApplicationModesStates.hpp"
#include "../../M20_Applications/Applications/Application.hpp"
#include "../../M20_Applications/ApplicationsManager.hpp"
#include "../../M90_Utilities/Math/MathUtilities.hpp"
#include <cstdint>

ApplicationModesStates::ApplicationModesStates(
    States& states,
    ApplicationsManager& applicationsManager)
:
    _states(states),
    _applicationsManager(applicationsManager),
    _selectedApplicationMode(EApplicationMode::Start)
{
}

ApplicationModesStates::EApplicationMode ApplicationModesStates::GetSelectedApplicationMode() const
{
    return _selectedApplicationMode;
}

void ApplicationModesStates::SetSelectedApplicationMode(
    EApplicationMode applicationMode)
{
    _selectedApplicationMode = applicationMode;
}

void ApplicationModesStates::ExecuteS040State()
{
    FilterSelectableApplicationModes();
    _selectedApplicationMode = EApplicationMode::Start;
}

void ApplicationModesStates::FilterSelectableApplicationModes()
{
    _selectableApplicationModes.clear();

    for (
        uint8_t applicationModeIndex = 0;
        applicationModeIndex < static_cast<uint16_t>(EApplicationMode::Last);
        applicationModeIndex++)
    {
        const Application* activeApplication = _applicationsManager.GetActiveApplication();
        auto applicationMode = 
            static_cast<EApplicationMode>(applicationModeIndex);
        bool add = true;

        switch (applicationMode)
        {
        case EApplicationMode::Start:
            // Only add start when no application is active.
            add = (activeApplication == nullptr);
            break;

        case EApplicationMode::Running:
            // Never add running (why is this?) TODO
            add = false;
            break;

        case EApplicationMode::Resume: // fall through
        case EApplicationMode::Quit:
            // Only add running/resume when application is paused.
            add = ((activeApplication != nullptr) && _applicationsManager.IsPaused());
            break;

        case EApplicationMode::Highscores: // Fall through 
        case EApplicationMode::ResetHighscores:
            // Only add high scores or reset high scores when it is a game.
            add = (_states.GetApplicationSelectionStates().GetSelectedApplicationType() == 
                Application::EType::Game);
            break;

        // Only add Settings and reset settings (TODO ?) when no application is active.
        case EApplicationMode::Settings: // Fall through 
        case EApplicationMode::ResetSettings:
            add = (activeApplication == nullptr);
            break;

        default:
            // Ignore.
            break;
        }

        if (add)
        {
            _selectableApplicationModes.push_back(
                static_cast<EApplicationMode>(applicationModeIndex));
        }
    }
}

std::vector<ApplicationModesStates::EApplicationMode> 
    ApplicationModesStates::GetSelectableApplicationModes() const
{
    return _selectableApplicationModes;
}

void ApplicationModesStates::OnJoystickUp()
{
    switch (_selectedApplicationMode)
    {
    case EApplicationMode::Start:
        _selectedApplicationMode = 
            static_cast<EApplicationMode>(static_cast<uint16_t>(EApplicationMode::Last) - 1);
        break;

    case EApplicationMode::Running:
        // Do nothing
        break;

    case EApplicationMode::Resume:
        _selectedApplicationMode = EApplicationMode::Quit;
        break;

    case EApplicationMode::Quit:
        _selectedApplicationMode = EApplicationMode::Resume;
        break;

    case EApplicationMode::Settings:
        _selectedApplicationMode = EApplicationMode::Start;
        break;

    case EApplicationMode::MakeFavorite:
        if (_states.GetApplicationSelectionStates().GetSelectedApplicationType() == 
            Application::EType::Game)
        {
            _selectedApplicationMode = EApplicationMode::Highscores;
        }
        else
        {
            _selectedApplicationMode = EApplicationMode::Settings;
        }
        break;

    case EApplicationMode::ResetNrOfTimesStarted:
        if (_states.GetApplicationSelectionStates().GetSelectedApplicationType() == 
            Application::EType::Game)
        {
            _selectedApplicationMode = EApplicationMode::ResetHighscores;
        }
        else
        {
            _selectedApplicationMode = EApplicationMode::ResetSettings;
        }
        break;

    default:
        _selectedApplicationMode = MathUtilities::WrapEnum(
            _selectedApplicationMode, -1, static_cast<uint8_t>(EApplicationMode::Last));
        break;
    }

    FilterSelectableApplicationModes();
}

void ApplicationModesStates::OnJoystickDown()
{
    switch (_selectedApplicationMode)
    {
    case EApplicationMode::Start:
        _selectedApplicationMode = EApplicationMode::Settings;
        break;

    case EApplicationMode::Running:
        // Do nothing
        break;

    case EApplicationMode::Resume:
        _selectedApplicationMode = EApplicationMode::Quit;
        break;

    case EApplicationMode::Quit:
        _selectedApplicationMode = EApplicationMode::Resume;
        break;

    case EApplicationMode::Settings:
        if (_states.GetApplicationSelectionStates().GetSelectedApplicationType() ==
            Application::EType::Game)
        {
            _selectedApplicationMode = EApplicationMode::Highscores;
        }
        else
        {
            _selectedApplicationMode = EApplicationMode::MakeFavorite;
        }
        break;

    case EApplicationMode::ResetSettings:
        if (_states.GetApplicationSelectionStates().GetSelectedApplicationType() == 
            Application::EType::Game)
        {
            _selectedApplicationMode = EApplicationMode::ResetHighscores;
        }
        else
        {
            _selectedApplicationMode = EApplicationMode::ResetNrOfTimesStarted;
        }
        break;

    default:
        _selectedApplicationMode = MathUtilities::WrapEnum(
            _selectedApplicationMode, +1, static_cast<uint8_t>(EApplicationMode::Last));
        break;
    }

    FilterSelectableApplicationModes();
}

void ApplicationModesStates::ProcessApplicationMode()
{
    switch (GetSelectedApplicationMode())
    {
    case EApplicationMode::Start: 
    {
        _states.StartApplication();
        _selectedApplicationMode = EApplicationMode::Running;

        // Sync NVS settings when starting an application as the timer of the menu is not called 
        // anymore.
        _applicationsManager.SyncNvsSettings(); 
    }
    break;

    case EApplicationMode::Resume:
    {
        _states.ResumeApplication();
        _selectedApplicationMode = EApplicationMode::Running;
    }
    break;

    case EApplicationMode::Quit:
    {
        _states.StopApplication();
        _selectedApplicationMode = EApplicationMode::Start;
    }
    break;

    case EApplicationMode::Highscores:
        // TODO // NOSONAR: S125 Remove commented out code
        // _selectedHighscoreIndex = 0;
        // SetState(States::EState::S050_Highscores);
        break;

    default:
        // Ignore.
        break;
    }
}
