#include "States.hpp"
#include "MenuApplication.hpp"
#include "../Games/Highscores.hpp"
#include "../ApplicationsManager.hpp"
#include "../Nvs/NvsSettings.hpp"
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
    _random(random),
    _applicationsManager(applicationsManager),
    _currentState(EState::S000_Welcome),
    _previousState(EState::S900_SettingInteger),
    _timeInCurrentState(TimeUtilities::GetCurrentTimeInUs()),
    _timeSinceNvsSync(TimeUtilities::GetCurrentTimeInUs()),
    _selectedAppMode(EAppMode::Idle),
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

    case EState::S040_AppMode:
        _selectedAppMode = EAppMode::Idle;
        break;

    default:
        // Ignore others
        break;
    }
}

void States::FilterSelectableTags()
{
    _selectableTags.clear();
    for (uint16_t applicationIndex = 0; applicationIndex < ApplicationsInfo::GetNrOfApplications(); 
        applicationIndex++)
    {
        if (ApplicationsInfo::GetTypeByIndex(applicationIndex) == GetSelectedAppType())
        {
            for (IApplication::ETag tag : ApplicationsInfo::GetTagsByIndex(applicationIndex))
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

std::vector<uint16_t> States::GetSelectableApplicationIndices() const
{
    return _selectableApplicationIndices;
}

void States::FilterSelectableApplications()
{
    _selectableApplicationIndices.clear();
    for (uint16_t applicationIndex = 0; applicationIndex < ApplicationsInfo::GetNrOfApplications();
        applicationIndex++)
    {
        if (ApplicationsInfo::GetNameByIndex(applicationIndex) == MenuApplication::NAME)
        {
            continue;
        }

        if (ApplicationsInfo::GetTypeByIndex(applicationIndex) != GetSelectedAppType())
        {
            continue;
        }

        bool append = false;
        switch (GetSelectedViewMode())
        {
        using enum States::EViewMode;
        case Alphabetic:
            append = true;
            break;

        case Favorites:
            append = ApplicationsInfo::GetFavoriteByIndex(applicationIndex);
            break;

        case MostUsed:
            append = true;
            break;

        case New:
            append = ApplicationsInfo::IsNewByIndex(applicationIndex);
            break;

        case Random:
            append = true;
            break;

        case Recent:
            append = true;
            break;

        case Tag:
        {
            for (IApplication::ETag tag : ApplicationsInfo::GetTagsByIndex(applicationIndex))
            {
                if (tag == _selectableTags[GetSelectedTagIndex()])
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
            _selectableApplicationIndices.push_back(applicationIndex);
        }

    }
}

void States::SortSelectableApplications()
{
    switch (GetSelectedViewMode())
    {
    case EViewMode::Alphabetic: // fallthrough
    case EViewMode::Favorites: // fallthrough
    case EViewMode::New: // fallthrough
    case EViewMode::Tag: // fallthrough
        std::sort(
            _selectableApplicationIndices.begin(),
            _selectableApplicationIndices.end(),
            [](uint16_t a, uint16_t b)
            {
                return ApplicationsInfo::GetNameByIndex(a) >
                       ApplicationsInfo::GetNameByIndex(b);
            }
        );
        break;

    case EViewMode::MostUsed:
    {
        std::sort(
            _selectableApplicationIndices.begin(),
            _selectableApplicationIndices.end(),
            [](uint16_t a, uint16_t b)
            {
                return ApplicationsInfo::GetNrOfStartsByIndex(a) >
                       ApplicationsInfo::GetNrOfStartsByIndex(b);
            }
        );
    }
    break;

    case EViewMode::Random:
    {
        /// @details S2245: not for security reasons, but for randomizing the order of applications
        std::mt19937 rng{ _random.GetNext() }; // NOSONAR S2245 

        std::shuffle( // NOSONAR S2245
            _selectableApplicationIndices.begin(),
            _selectableApplicationIndices.end(),
            rng
        );
    }
    break;

    case EViewMode::Recent:
        std::sort(
            _selectableApplicationIndices.begin(),
            _selectableApplicationIndices.end(),
            [](uint16_t a, uint16_t b)
            {
                return ApplicationsInfo::GetLastStartTimeByIndex(a) >
                       ApplicationsInfo::GetLastStartTimeByIndex(b);
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
    return _applicationsManager.GetNvsSettings().GetLastSelectedAppIndex();
}

void States::SetSelectedAppIndex(
    uint16_t index)
{
    _applicationsManager.GetNvsSettings().SetLastSelectedAppIndex(index);
}

States::EViewMode States::GetSelectedViewMode() const
{
    return (States::EViewMode)_applicationsManager.GetNvsSettings().GetLastSelectedViewModeIndex();
}

void States::SetSelectedViewMode(
    EViewMode selectedViewMode)
{
    _applicationsManager.GetNvsSettings().SetLastSelectedViewModeIndex((uint8_t) selectedViewMode);
}

uint8_t States::GetSelectedTagIndex() const
{
    return _applicationsManager.GetNvsSettings().GetLastSelectedTagIndex();
}

void States::SetSelectedTagIndex(
    uint8_t selectedTagIndex)
{
    _applicationsManager.GetNvsSettings().SetLastSelectedTagIndex(selectedTagIndex);
}

Application::EType States::GetSelectedAppType() const
{
    return (Application::EType)_applicationsManager.GetNvsSettings().GetLastSelectedAppTypeIndex();
}

void States::SetSelectedAppType(
    Application::EType selectedAppType)
{
    _applicationsManager.GetNvsSettings().SetLastSelectedAppTypeIndex((uint8_t) selectedAppType);
}

States::EAppMode States::GetSelectedAppMode() const
{
    return _selectedAppMode;
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
    std::chrono::microseconds elapsedMsInCurrentState = TimeUtilities::GetUsSince(_timeInCurrentState);

    switch (_currentState)
    {
    case EState::S000_Welcome:
        if (elapsedMsInCurrentState >= WELCOME_STATE_TIME)
        {
            SetState(EState::S010_SelectAppType);
            changed = true;
        }
        break;

    default: /* ignore others */
        break;
    }

    if (std::chrono::microseconds elapsedMsSinceNvsSync = 
        TimeUtilities::GetUsSince(_timeSinceNvsSync); 
        elapsedMsSinceNvsSync >= NVS_SYNC_TIME)
    {
        _applicationsManager.SyncNvsSettings();
    }

    return changed;
}

void States::OnSystemButtonPressed()
{
    switch (_currentState) // NOSONAR: S1301 keep switch instead of if
    {
    case EState::S040_AppMode:
        if (_selectedAppMode == EAppMode::Running)
        {
            IApplication::EId applicationId = _applicationsManager.GetActiveApplicationId();
            _applicationsManager.PauseApplication(applicationId);
            _selectedAppMode = EAppMode::Paused;
        }
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
    default: 
        // Ignore others
        break;
    }
}

void States::OnJoystickLeft()
{
    switch (_currentState)
    {
    case EState::S020_SelectViewMode: SetState(EState::S010_SelectAppType); break;
    case EState::S021_SelectTag: SetState(EState::S020_SelectViewMode); break;
    case EState::S030_SelectApp: SetState(EState::S020_SelectViewMode); break;
    case EState::S040_AppMode: 
        if ((_selectedAppMode != EAppMode::Paused) &&
            (_selectedAppMode != EAppMode::Quit))
        {
            SetState(EState::S030_SelectApp); break;
        }
        break;

    default: 
        // Ignore others.
        break;
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
        SetSelectedAppType(MathUtilities::WrapEnum(GetSelectedAppType(), -1, count));
        break;

    case EState::S020_SelectViewMode:
        count = static_cast<int>(EViewMode::Last);
        SetSelectedViewMode(MathUtilities::WrapEnum(GetSelectedViewMode(), -1, count));
        break;

    case EState::S021_SelectTag: 
        if (!_selectableTags.empty())
        {
            SetSelectedTagIndex(MathUtilities::WrapEnum(
                GetSelectedTagIndex(), -1, static_cast<int>(_selectableTags.size())));
        }
        break;

    case EState::S030_SelectApp:
        SetSelectedAppIndex(static_cast<uint16_t>(MathUtilities::Clamp(
            GetSelectedAppIndex() - 1, 0, GetSelectableApplicationIndices().size() - 1)));
        break;

    case EState::S040_AppMode: 
        OnJoystickUpS040_AppMode();
        break;

    default:
        // Ignore all others
        break;
    }
}

void States::OnJoystickUpS040_AppMode()
{
    switch (_selectedAppMode)
    {
    case EAppMode::Idle:
        _selectedAppMode = static_cast<EAppMode>(static_cast<uint16_t>(EAppMode::Last) - 1);
        break;

    case EAppMode::Running:
        // Do nothing
        break;

    case EAppMode::Paused:
        _selectedAppMode = EAppMode::Quit;
        break;

    case EAppMode::Quit:
        _selectedAppMode = EAppMode::Paused;
        break;

    case EAppMode::Settings:
        _selectedAppMode = EAppMode::Idle;
        break;

    case EAppMode::Highscores:
        _selectedHighscoreIndex = (_selectedHighscoreIndex + Highscores::MAX_NR_OF_ENTRIES  - 1) %
            Highscores::MAX_NR_OF_ENTRIES;
        break;


    default:
        _selectedAppMode = MathUtilities::WrapEnum(
            _selectedAppMode, -1, static_cast<uint8_t>(EAppMode::Last));
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
        SetSelectedAppType(MathUtilities::WrapEnum(GetSelectedAppType(), 1, count));
        break;

    case EState::S020_SelectViewMode:
        count = static_cast<int>(EViewMode::Last);
        SetSelectedViewMode(MathUtilities::WrapEnum(GetSelectedViewMode(), 1, count));
        break;

    case EState::S021_SelectTag: 
        if (!_selectableTags.empty())
        {
            SetSelectedTagIndex(MathUtilities::WrapEnum(
                GetSelectedTagIndex(), 1, static_cast<int>(_selectableTags.size())));
        }
        break;

    case EState::S030_SelectApp:
        SetSelectedAppIndex(static_cast<uint16_t>(MathUtilities::Clamp(
            GetSelectedAppIndex() + 1, 0, GetSelectableApplicationIndices().size() - 1)));
        break;

    case EState::S040_AppMode:
        OnJoystickDownS040_AppMode();
        break;
       
    default: 
        // Ignore others
        break;
    }
}

void States::OnJoystickDownS040_AppMode()
{
    switch (_selectedAppMode)
    {
    case EAppMode::Idle:
        _selectedAppMode = EAppMode::Settings;
        break;

    case EAppMode::Running:
        // Do nothing
        break;

    case EAppMode::Paused:
        _selectedAppMode = EAppMode::Quit;
        break;

    case EAppMode::Quit:
        _selectedAppMode = EAppMode::Paused;
        break;

    case EAppMode::Highscores:
        _selectedHighscoreIndex = (_selectedHighscoreIndex + 1) % Highscores::MAX_NR_OF_ENTRIES;
        break;

    default:
        _selectedAppMode = MathUtilities::WrapEnum(
            _selectedAppMode, +1, static_cast<uint8_t>(EAppMode::Last));
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
        SetState(EState::S010_SelectAppType);
        break;

    case EState::S010_SelectAppType:
        SetState(EState::S020_SelectViewMode); 
        break;

    case EState::S020_SelectViewMode: 
        SetState(GetSelectedViewMode() == EViewMode::Tag 
            ? EState::S021_SelectTag 
            : EState::S030_SelectApp);
        break;

    case EState::S021_SelectTag:
        if (!GetSelectableTags().empty())
        {
            SetState(EState::S030_SelectApp);
        }
        break;

    case EState::S030_SelectApp: 
        if (!_selectableApplicationIndices.empty())
        {
            SetState(EState::S040_AppMode);
        }
        break;

    case EState::S040_AppMode: 
        ProcessAppMode();
        break;

    default: 
        break; // Ignore
    }
}

void States::ProcessAppMode()
{
    switch (GetSelectedAppMode())
    {
    case EAppMode::Idle: // Start
    {
        IApplication::EId applicationIdToStart = ApplicationsInfo::GetIdByIndex(
            GetSelectableApplicationIndices()[GetSelectedAppIndex()]);
        _applicationsManager.StartApplication(applicationIdToStart);
        _selectedAppMode = EAppMode::Running;

        // Sync NVS settings when starting an application as the timer of the menu is not called 
        // anymore.
        _applicationsManager.SyncNvsSettings(); 
    }
    break;

    case EAppMode::Paused: // Resume
    {
        IApplication::EId applicationIdToResume = ApplicationsInfo::GetIdByIndex(
            GetSelectableApplicationIndices()[GetSelectedAppIndex()]);
        _applicationsManager.ResumeApplication(applicationIdToResume);
        _selectedAppMode = EAppMode::Running;
    }
    break;

    case EAppMode::Quit:
    {
        IApplication::EId applicationIdToQuit = ApplicationsInfo::GetIdByIndex(
            GetSelectableApplicationIndices()[GetSelectedAppIndex()]);
        _applicationsManager.StopApplication(applicationIdToQuit);
        _selectedAppMode = EAppMode::Idle;
    }
    break;

    case EAppMode::Highscores:
        _selectedHighscoreIndex = 0;
        SetState(States::EState::S050_Highscores);
        break;

    default:
        // Ignore.
        break;
    }
}
