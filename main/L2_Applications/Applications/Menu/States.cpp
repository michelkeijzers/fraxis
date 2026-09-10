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
    case EViewMode::Alphabetic: // fallthrough
    case EViewMode::Favorites: // fallthrough
    case EViewMode::New: // fallthrough
    case EViewMode::Tag: // fallthrough
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
    case EState::S040_AppMode:
        if (_selectedAppMode == EAppMode::Running)
        {
            Application& application = _applicationsManager.GetActiveApplication();
            _applicationsManager.PauseApplication(application);
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
        _selectedAppTypeIndex = MathUtilities::WrapEnum(_selectedAppTypeIndex, -1, count);
        break;

    case EState::S020_SelectViewMode:
        count = static_cast<int>(EViewMode::Last);
        _selectedViewModeIndex = MathUtilities::WrapEnum(_selectedViewModeIndex, -1, count);
        break;

    case EState::S021_SelectTag: 
        _selectedAppIndex = 0;
        if (!_selectableTags.empty())
        {
            _selectedTagIndex = MathUtilities::WrapEnum(
                _selectedTagIndex, -1, static_cast<int>(_selectableTags.size()));
        }
        break;

    case EState::S030_SelectApp:
        _selectedAppIndex = static_cast<uint16_t>(MathUtilities::Clamp(
            GetSelectedAppIndex() - 1, 0, GetSelectableApplications().size() - 1));
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
        _selectedAppTypeIndex = MathUtilities::WrapEnum(_selectedAppTypeIndex, 1, count);
        break;

    case EState::S020_SelectViewMode:
        count = static_cast<int>(EViewMode::Last);
        _selectedViewModeIndex = MathUtilities::WrapEnum(_selectedViewModeIndex, 1, count);
        break;

    case EState::S021_SelectTag: 
        _selectedAppIndex = 0;
        if (!_selectableTags.empty())
        {
            _selectedTagIndex = MathUtilities::WrapEnum(
                _selectedTagIndex, 1, static_cast<int>(_selectableTags.size()));
        }
        break;

    case EState::S030_SelectApp:
        _selectedAppIndex = static_cast<uint16_t>(MathUtilities::Clamp(
            GetSelectedAppIndex() + 1, 0, GetSelectableApplications().size() - 1));
        break;

    case EState::S040_AppMode:
        OnJoystickDownS040_AppMode();
        break;
       
        //_selectedHighscoreIndex = MathUtilities::WrapEnum(_selectedHighscoreIndex, -1, _MAX_HIGH_SCORES_ENTRIES);

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
        Application* applicationToStart = GetSelectableApplications()[GetSelectedAppIndex()];
        _applicationsManager.StartApplication(*applicationToStart);
        _selectedAppMode = EAppMode::Running;
    }
    break;

    case EAppMode::Paused: // Resume
    {
        Application* applicationToResume = GetSelectableApplications()[GetSelectedAppIndex()];
        _applicationsManager.ResumeApplication(*applicationToResume);
        _selectedAppMode = EAppMode::Running;
    }
    break;

    case EAppMode::Quit:
    {
        Application* applicationToQuit = GetSelectableApplications()[GetSelectedAppIndex()];
        _applicationsManager.StopApplication(*applicationToQuit);
        _selectedAppMode = EAppMode::Idle;
    }
    break;

    default:
        // Ignore.
        break;
    }
}
