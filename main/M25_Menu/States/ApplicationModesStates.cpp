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

        using enum EApplicationMode;
        switch (applicationMode)
        {
        case Start:
            // Only add start when no application is active.
            add = (activeApplication == nullptr);
            break;

        case Running:
            // Never add running (why is this?) NOSONAR TODO
            add = false;
            break;

        case Resume: // fall through
        case Quit:
            // Only add running/resume when application is paused.
            add = ((activeApplication != nullptr) && _applicationsManager.IsPaused());
            break;

        case Highscores: // Fall through 
        case ResetHighscores:
            // Only add high scores or reset high scores when it is a game.
            add = (_states.GetApplicationSelectionStates().GetSelectedApplicationType() == 
                Application::EType::Game);
            break;

        // Only add Settings and reset settings (NOSONAR TODO ?) when no application is active.
        case Settings: // Fall through 
        case ResetSettings:
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
    using enum EApplicationMode;
    switch (_selectedApplicationMode)
    {
    case Start:
        _selectedApplicationMode = 
            static_cast<EApplicationMode>(static_cast<uint16_t>(Last) - 1);
        break;

    case Running:
        // Do nothing
        break;

    case Resume:
        _selectedApplicationMode = Quit;
        break;

    case Quit:
        _selectedApplicationMode = Resume;
        break;

    case Settings:
        _selectedApplicationMode = Start;
        break;

    case MakeFavorite:
        if (_states.GetApplicationSelectionStates().GetSelectedApplicationType() == 
            Application::EType::Game)
        {
            _selectedApplicationMode = Highscores;
        }
        else
        {
            _selectedApplicationMode = Settings;
        }
        break;

    case ResetNrOfTimesStarted:
        if (_states.GetApplicationSelectionStates().GetSelectedApplicationType() == 
            Application::EType::Game)
        {
            _selectedApplicationMode = ResetHighscores;
        }
        else
        {
            _selectedApplicationMode = ResetSettings;
        }
        break;

    default:
        _selectedApplicationMode = MathUtilities::WrapEnum(
            _selectedApplicationMode, -1, static_cast<uint8_t>(Last));
        break;
    }

    FilterSelectableApplicationModes();
}

void ApplicationModesStates::OnJoystickDown()
{
    using enum EApplicationMode;
    switch (_selectedApplicationMode)
    {
    case Start:
        _selectedApplicationMode = Settings;
        break;

    case Running:
        // Do nothing
        break;

    case Resume:
        _selectedApplicationMode = Quit;
        break;

    case Quit:
        _selectedApplicationMode = Resume;
        break;

    case Settings:
        if (_states.GetApplicationSelectionStates().GetSelectedApplicationType() ==
            Application::EType::Game)
        {
            _selectedApplicationMode = Highscores;
        }
        else
        {
            _selectedApplicationMode = MakeFavorite;
        }
        break;

    case ResetSettings:
        if (_states.GetApplicationSelectionStates().GetSelectedApplicationType() == 
            Application::EType::Game)
        {
            _selectedApplicationMode = ResetHighscores;
        }
        else
        {
            _selectedApplicationMode = ResetNrOfTimesStarted;
        }
        break;

    default:
        _selectedApplicationMode = MathUtilities::WrapEnum(
            _selectedApplicationMode, +1, static_cast<uint8_t>(Last));
        break;
    }

    FilterSelectableApplicationModes();
}

void ApplicationModesStates::ProcessApplicationMode()
{
    using enum EApplicationMode;
    switch (GetSelectedApplicationMode())
    {
    case Start: 
    {
        _states.StartApplication();
        _selectedApplicationMode = Running;

        // Sync NVS settings when starting an application as the timer of the menu is not called 
        // anymore.
        _applicationsManager.SyncNvsSettings(); 
    }
    break;

    case Resume:
    {
        _states.ResumeApplication();
        _selectedApplicationMode = Running;
    }
    break;

    case EApplicationMode::Quit:
    {
        _states.StopApplication();
        _selectedApplicationMode = EApplicationMode::Start;
    }
    break;

    case EApplicationMode::Highscores:
        // NOSONAR TODO highscores
        // _selectedHighscoreIndex = 0;
        // SetState(States::EState::S050_Highscores);
        break;

    default:
        // Ignore.
        break;
    }
}
