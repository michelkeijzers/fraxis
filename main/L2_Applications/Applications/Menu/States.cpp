#include "States.hpp"
#include "MenuApplication.hpp"
#include "../../ApplicationsManager.hpp"
#include "../../../L3_Messages/Types.hpp"
#include "../../../L8_Services/Random/Random.hpp"
#include "../../../L9_Utilities/Assert/Assert.hpp"
#include "../../../L9_Utilities/Log/Log.hpp"
#include "../../../L9_Utilities/Math/MathUtilities.hpp"
#include "../../../L9_Utilities/Time/TimeUtilities.hpp"
#include <algorithm>
#include <random>

using namespace std;

States::States(
    Random& random,
    ApplicationsManager& applicationsManager)
: 
    _random(random),
    _applicationsManager(applicationsManager),
    _currentState(EState::S000_Welcome),
    _previousState(EState::S900_SettingInteger),
    _timeInCurrentState(TimeUtilities::GetCurrentTimeInUs()),
    _selectedAppTypeIndex(Application::EType::Game),
    _selectedViewModeIndex(EViewMode::Recent),
    _selectedTagIndex(0),
    _selectedAppIndex(0),
    _selectedHighscoreIndex(0),
    _swapFavoriteStatus(false)
{
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
        FilterSelectableTags();
        break;

    case EState::S030_SelectApp:
        FilterSelectableApplications();
        break;

    default:
        // Ignore others
        break;
    }
}

void States::FilterSelectableTags()
{
    _selectableTags.clear();
    for (auto& application : _applicationsManager.GetApplications())
    {
        if (application->GetType() == _selectedAppTypeIndex)
        {
            for (auto& tag : application->GetTags())
            {
                if (std::find(_selectableTags.begin(), _selectableTags.end(), tag) == 
                    _selectableTags.end())
                {
                    _selectableTags.push_back(tag);
                }
            }
        }
    }
}

std::vector<Application::ETag> States::GetSelectableTags() const
{
    return _selectableTags;
}


std::vector<Application*> States::GetSelectableApplications() const
{
    return _selectableApplications;
}

void States::FilterSelectableApplications()
{
    _selectableApplications.clear();
    for (const auto& application : _applicationsManager.GetApplications())
    {
        Application* applicationPointer = application.get();
        if (applicationPointer->GetName() == MenuApplication::NAME)
        {
            continue;
        }

        if (applicationPointer->GetType() != _selectedAppTypeIndex)
        {
            continue;
        }

        bool append = false;
        switch (_selectedViewModeIndex)
        {
        case EViewMode::Alphabetic:
            append = true;
            break;

        case EViewMode::Favorites:
            append = applicationPointer->IsFavorite();
            break;

        case EViewMode::MostUsed:
            append = true;
            break;

        case EViewMode::New:
            append = applicationPointer->IsNew();
            break;

        case EViewMode::Random:
            append = true;
            break;

        case EViewMode::Recent:
            append = true;
            break;

        case EViewMode::Tag:
        {
            for (auto tag : applicationPointer->GetTags())
            {
                if (tag == _selectableTags[_selectedTagIndex])
                {
                    append = true;
                    break;
                }
            }
            break;
        }
        
        default:
            Assert::Fail(Types::ETaskId::ApplicationsTask, "Unknown tag");
            break;
        }

        if (append)
        {
            _selectableApplications.push_back(applicationPointer);
        }

    }
}

void States::SortSelectableApplications()
{
    switch (_selectedViewModeIndex)
    {
    case EViewMode::Alphabetic: // breakthrough
    case EViewMode::Favorites: // breakthrough
    case EViewMode::New: // breakthrough
    case EViewMode::Tag: // breakthrough
        std::sort(
            _selectableApplications.begin(),
            _selectableApplications.end(),
            [](const Application* a, const Application* b)
            {
                return a->GetName() < b->GetName();
            }
        );
        break;

    case EViewMode::MostUsed:
    {
        std::sort(
            _selectableApplications.begin(),
            _selectableApplications.end(),
            [](const Application* a, const Application* b)
            {
                return a->GetNrOfStarts() < b->GetNrOfStarts();
            }
        );
    }
    break;

    case EViewMode::Random:
    {
        std::mt19937 rng{ _random.GetNext() };

        std::shuffle(
            _selectableApplications.begin(),
            _selectableApplications.end(),
            rng
        );
    }
    break;

    case EViewMode::Recent:
        std::sort(
            _selectableApplications.begin(),
            _selectableApplications.end(),
            [](const Application* a, const Application* b)
            {
                return a->GetLastStartTime() < b->GetLastStartTime();
            }
        );
        break;        break;

    default:
        Assert::Fail(Types::ETaskId::ApplicationsTask, "Unknown tag");
        break;
    }
}

uint16_t States::GetSelectedAppIndex() const
{
    return _selectedAppIndex;
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
    uint64_t elapsedMs = TimeUtilities::GetUsSince(_timeInCurrentState);

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
    switch (_currentState)
    {
    /// @todo: Following case statement is temporary (to be handled by running app).
    case EState::S041_AppRunning:
        SetState(EState::S043_AppPaused);
        break;

    case EState::S043_AppPaused:
        //Ignore
        break;

    case EState::S044_AppQuit:
        SetState(EState::S045_AppConfirmQuit);
        break;

    case EState::S045_AppConfirmQuit:
        SetState(EState::S040_AppStart);
        break;

    default:
        SetState(EState::S010_SelectAppType); // Return home
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
    default: break; // Ignore others
    }
}

void States::OnJoystickLeft()
{
    switch (_currentState)
    {
    case EState::S020_SelectViewMode: SetState(EState::S010_SelectAppType); break;
    case EState::S021_SelectTag: SetState(EState::S020_SelectViewMode); break;
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

    switch (_currentState)
    {
    case EState::S000_Welcome: 
        SetState(EState::S010_SelectAppType); 
        break;
        
    case EState::S010_SelectAppType: 
        count = static_cast<int>(Application::EType::Last);
        _selectedAppTypeIndex = MathUtilities::WrapEnum(_selectedAppTypeIndex, -1, count);
        break;

    case EState::S020_SelectViewMode:
        count = static_cast<int>(EViewMode::Last);
        _selectedViewModeIndex = MathUtilities::WrapEnum(_selectedViewModeIndex, -1, count);
        break;

    case EState::S021_SelectTag: 
        _selectedAppIndex = 0;
        if (_selectableTags.size() > 0)
        {
            _selectedTagIndex = MathUtilities::WrapEnum(
                _selectedTagIndex, -1, static_cast<int>(_selectableTags.size()));
        }
        break;

    case EState::S030_SelectApp:
        _selectedAppIndex = static_cast<uint16_t>(MathUtilities::Clamp(
            GetSelectedAppIndex() - 1, 0, GetSelectableApplications().size() - 1));
        break;

    case EState::S040_AppStart: 
        SetState(EState::S090_SetAsFavorite); 
        break;

    case EState::S043_AppPaused: 
        SetState(EState::S044_AppQuit); 
        break;

    case EState::S044_AppQuit: 
        SetState(EState::S043_AppPaused); 
        break;

    case EState::S050_AppSettings: 
        SetState(EState::S040_AppStart); 
        break;

    case EState::S060_Highscores: 
        SetState(EState::S050_AppSettings); 
        break;

    case EState::S061_HighscoreDetails: 
        _selectedHighscoreIndex = MathUtilities::WrapEnum(_selectedHighscoreIndex, -1, _MAX_HIGH_SCORES_ENTRIES);
        break;

    case EState::S070_ResetHighscores: 
        SetState(EState::S060_Highscores); 
        break;

    case EState::S072_HighscoresResetDone: 
        SetState(EState::S060_Highscores); 
        break;

    case EState::S080_PlayerSetup: 
        SetState(EState::S070_ResetHighscores); 
        break;

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

    switch (_currentState)
    {
    case EState::S000_Welcome: 
        SetState(EState::S010_SelectAppType); 
        break;

    case EState::S010_SelectAppType: 
        count = static_cast<int>(Application::EType::Last);
        _selectedAppTypeIndex = MathUtilities::WrapEnum(_selectedAppTypeIndex, 1, count);
        break;

    case EState::S020_SelectViewMode:
        count = static_cast<int>(EViewMode::Last);
        _selectedViewModeIndex = MathUtilities::WrapEnum(_selectedViewModeIndex, 1, count);
        break;

    case EState::S021_SelectTag: 
        _selectedAppIndex = 0;
        if (_selectableTags.size() > 0)
        {
            _selectedTagIndex = MathUtilities::WrapEnum(
                _selectedTagIndex, 1, static_cast<int>(_selectableTags.size()));
        }
        break;

    case EState::S030_SelectApp:
        _selectedAppIndex = static_cast<uint16_t>(MathUtilities::Clamp(
            GetSelectedAppIndex() + 1, 0, GetSelectableApplications().size() - 1));
        break;

    case EState::S040_AppStart: 
        SetState(EState::S050_AppSettings); 
        break;

    case EState::S043_AppPaused: 
        SetState(EState::S044_AppQuit); 
        break;

    case EState::S044_AppQuit: 
        SetState(EState::S043_AppPaused); 
        break;

    case EState::S050_AppSettings: 
        SetState((_selectedAppTypeIndex == Application::EType::Game) 
            ? EState::S060_Highscores : EState::S090_SetAsFavorite);
        break;

    case EState::S060_Highscores: 
        SetState(EState::S070_ResetHighscores); 
        break;

    case EState::S061_HighscoreDetails:
        _selectedHighscoreIndex = MathUtilities::WrapEnum(_selectedHighscoreIndex, -1, _MAX_HIGH_SCORES_ENTRIES);
        break;

    case EState::S070_ResetHighscores: 
        SetState(EState::S080_PlayerSetup); 
        break;

    case EState::S072_HighscoresResetDone: 
        SetState(EState::S060_Highscores); 
        break;

    case EState::S080_PlayerSetup: 
        SetState(EState::S090_SetAsFavorite); 
        break;

    case EState::S090_SetAsFavorite: 
        SetState(EState::S040_AppStart); 
        break;

    default: 
        // Ignore others
        break;
    }
}

void States::OnJoystickRight()
{
    switch (_currentState)
    {
    case EState::S000_Welcome: 
        SetState(EState::S010_SelectAppType); 
        break;

    case EState::S010_SelectAppType: 
        SetState(EState::S020_SelectViewMode); 
        break;

    case EState::S020_SelectViewMode: 
        SetState(_selectedViewModeIndex == EViewMode::Tag ? EState::S021_SelectTag : EState::S030_SelectApp); 
        _selectedAppIndex = 0;
        _selectedTagIndex = 0;
        break;

    case EState::S021_SelectTag: 
        if (!GetSelectableTags().empty())
        {
            SetState(EState::S030_SelectApp);
            _selectedAppIndex = 0;
        }
        break;

    case EState::S030_SelectApp: 
        if (!_selectableApplications.empty())
        {
            SetState(EState::S040_AppStart);
        }
        break;
        
    case EState::S040_AppStart: 
        SetState(EState::S041_AppRunning);
        break;

    case EState::S043_AppPaused: 
        SetState(EState::S041_AppRunning); 
        break;

    case EState::S044_AppQuit: 
        SetState(EState::S045_AppConfirmQuit);
        break;

    case EState::S060_Highscores: 
        SetState(EState::S061_HighscoreDetails);
        break;

    case EState::S070_ResetHighscores: 
        SetState(EState::S071_ConfirmHighscoresReset);
        break;

    case EState::S072_HighscoresResetDone: 
        SetState(EState::S060_Highscores);
        break;

    case EState::S090_SetAsFavorite: 
        SetState(EState::S090_SetAsFavorite); // Rerender?
        _swapFavoriteStatus = true;
        break;

    default: 
        break; // Ignore
    }
}

void States::OnJoystickButtonPressed()
{
    switch (_currentState)
    {
    case EState::S010_SelectAppType: 
        SetState(EState::S020_SelectViewMode); 
        break;

    case EState::S020_SelectViewMode: 
        SetState(_selectedViewModeIndex == EViewMode::Tag ? EState::S021_SelectTag : EState::S030_SelectApp); 
        _selectedAppIndex = 0;
        _selectedTagIndex = 0;
        break;

    case EState::S021_SelectTag: 
        SetState(EState::S030_SelectApp);
        _selectedAppIndex = 0;
        break;

    case EState::S030_SelectApp: 
        SetState(EState::S040_AppStart);
        break;

    case EState::S040_AppStart: 
        SetState(EState::S041_AppRunning);
        break;

    case EState::S043_AppPaused: 
        SetState(EState::S041_AppRunning);
        break;

    case EState::S044_AppQuit: 
        SetState(EState::S045_AppConfirmQuit); 
        break;

    case EState::S060_Highscores: 
        SetState(EState::S061_HighscoreDetails); 
        break;

    case EState::S070_ResetHighscores: 
        SetState(EState::S071_ConfirmHighscoresReset); 
        break;

    case EState::S071_ConfirmHighscoresReset:
        SetState(EState::S072_HighscoresResetDone);
        break;

    case EState::S072_HighscoresResetDone: 
        SetState(EState::S060_Highscores);
        break;

    case EState::S090_SetAsFavorite: 
        SetState(EState::S090_SetAsFavorite); // Rerender?
        _swapFavoriteStatus = true;
        break;

    default: 
        break; // Ignore
    }
}
