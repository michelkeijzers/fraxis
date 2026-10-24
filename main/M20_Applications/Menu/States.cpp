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
    _selectedApplicationMode(EApplicationMode::Start),
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

    case EState::S030_SelectApplication:
        FilterSelectableApplications();
        break;

    case EState::S040_ApplicationMode:
        FilterSelectableApplicationModes();
        _selectedApplicationMode = EApplicationMode::Start;
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
        if (ApplicationsInfo::GetTypeByIndex(applicationIndex) == GetSelectedApplicationType())
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

void States::FilterSelectableApplicationModes()
{
    _selectableApplicationModes.clear();

    for (
        uint8_t applicationModeIndex = 0;
        applicationModeIndex < static_cast<uint16_t>(States::EApplicationMode::Last);
        applicationModeIndex++)
    {
        Application* activeApplication = _applicationsManager.GetActiveApplication();
        EApplicationMode applicationMode = 
            static_cast<States::EApplicationMode>(applicationModeIndex);
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
            add = (GetSelectedApplicationType() == Application::EType::Game);
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
                static_cast<States::EApplicationMode>(applicationModeIndex));
        }
    }
}

std::vector<Application::ETag> States::GetSelectableTags() const
{
    return _selectableTags;
}

std::vector<States::EApplicationMode> States::GetSelectableApplicationModes() const
{
    return _selectableApplicationModes;
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

        if (ApplicationsInfo::GetTypeByIndex(applicationIndex) != GetSelectedApplicationType())
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

uint16_t States::GetSelectedApplicationIndex() const
{
    return _applicationsManager.GetNvsSettings().GetLastSelectedApplicationIndex();
}

void States::SetSelectedApplicationIndex(
    uint16_t index)
{
    _applicationsManager.GetNvsSettings().SetLastSelectedApplicationIndex(index);
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

Application::EType States::GetSelectedApplicationType() const
{
    return (Application::EType)
        _applicationsManager.GetNvsSettings().GetLastSelectedApplicationTypeIndex();
}

void States::SetSelectedApplicationType(
    Application::EType selectedApplicationType)
{
    _applicationsManager.GetNvsSettings().SetLastSelectedApplicationTypeIndex(
        (uint8_t) selectedApplicationType);
}

States::EApplicationMode States::GetSelectedApplicationMode() const
{
    return _selectedApplicationMode;
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
    case EState::S040_ApplicationMode:
        if (_selectedApplicationMode == EApplicationMode::Running)
        {
            _applicationsManager.PauseApplication();
            _selectedApplicationMode = EApplicationMode::Resume;
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
        if ((_selectedApplicationMode != EApplicationMode::Resume) &&
            (_selectedApplicationMode != EApplicationMode::Quit))
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
    int count;

    switch (_currentState)
    {
    case EState::S000_Welcome: 
        SetState(EState::S010_SelectApplicationType); 
        break;
        
    case EState::S010_SelectApplicationType: 
        count = static_cast<int>(Application::EType::Last);
        SetSelectedApplicationType(
            MathUtilities::WrapEnum(GetSelectedApplicationType(), -1, count));
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

    case EState::S030_SelectApplication:
        SetSelectedApplicationIndex(static_cast<uint16_t>(MathUtilities::Clamp(
            GetSelectedApplicationIndex() - 1, 0, GetSelectableApplicationIndices().size() - 1)));
        break;

    case EState::S040_ApplicationMode: 
        OnJoystickUpS040_ApplicationMode();
        break;

    default:
        // Ignore all others
        break;
    }
}

void States::OnJoystickUpS040_ApplicationMode()
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
        if (GetSelectedApplicationType() == Application::EType::Game)
        {
            _selectedApplicationMode = EApplicationMode::Highscores;
        }
        else
        {
            _selectedApplicationMode = EApplicationMode::Settings;
        }
        break;

    case EApplicationMode::ResetNrOfTimesStarted:
        if (GetSelectedApplicationType() == Application::EType::Game)
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

void States::OnJoystickDown()
{
    int count;

    switch (_currentState)
    {
    case EState::S000_Welcome: 
        SetState(EState::S010_SelectApplicationType); 
        break;

    case EState::S010_SelectApplicationType: 
        count = static_cast<int>(Application::EType::Last);
        SetSelectedApplicationType(MathUtilities::WrapEnum(GetSelectedApplicationType(), 1, count));
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

    case EState::S030_SelectApplication:
        SetSelectedApplicationIndex(static_cast<uint16_t>(MathUtilities::Clamp(
            GetSelectedApplicationIndex() + 1, 0, GetSelectableApplicationIndices().size() - 1)));
        break;

    case EState::S040_ApplicationMode:
        OnJoystickDownS040_ApplicationMode();
        break;

    default: 
        // Ignore others
        break;
    }
}

void States::OnJoystickDownS040_ApplicationMode()
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
        if (GetSelectedApplicationType() == Application::EType::Game)
        {
            _selectedApplicationMode = EApplicationMode::Highscores;
        }
        else
        {
            _selectedApplicationMode = EApplicationMode::MakeFavorite;
        }
        break;

    case EApplicationMode::ResetSettings:
        if (GetSelectedApplicationType() == Application::EType::Game)
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
        SetState(GetSelectedViewMode() == EViewMode::Tag 
            ? EState::S021_SelectTag 
            : EState::S030_SelectApplication);
        break;

    case EState::S021_SelectTag:
        if (!GetSelectableTags().empty())
        {
            SetState(EState::S030_SelectApplication);
        }
        break;

    case EState::S030_SelectApplication: 
        if (!_selectableApplicationIndices.empty())
        {
            SetState(EState::S040_ApplicationMode);
        }
        break;

    case EState::S040_ApplicationMode: 
        ProcessApplicationMode();
        break;

    default: 
        break; // Ignore
    }
}

void States::ProcessApplicationMode()
{
    switch (GetSelectedApplicationMode())
    {
    case EApplicationMode::Start: 
    {
        EApplicationId applicationIdToStart = ApplicationsInfo::GetIdByIndex(
            GetSelectableApplicationIndices()[GetSelectedApplicationIndex()]);
        _applicationsManager.StartApplication(applicationIdToStart);
        _selectedApplicationMode = EApplicationMode::Running;

        // Sync NVS settings when starting an application as the timer of the menu is not called 
        // anymore.
        _applicationsManager.SyncNvsSettings(); 
    }
    break;

    case EApplicationMode::Resume:
    {
        _applicationsManager.ResumeApplication();
        _selectedApplicationMode = EApplicationMode::Running;
    }
    break;

    case EApplicationMode::Quit:
    {
        EApplicationId applicationIdToQuit = ApplicationsInfo::GetIdByIndex(
            GetSelectableApplicationIndices()[GetSelectedApplicationIndex()]);
        _applicationsManager.StopApplication(applicationIdToQuit);
        _selectedApplicationMode = EApplicationMode::Start;
    }
    break;

    case EApplicationMode::Highscores:
        _selectedHighscoreIndex = 0;
        SetState(States::EState::S050_Highscores);
        break;

    default:
        // Ignore.
        break;
    }
}
