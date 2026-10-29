#include "ApplicationSelectionStates.hpp"
#include "../../M20_Applications/ApplicationsManager.hpp"
#include "../../M20_Applications/Nvs/NvsSettings.hpp"
#include "../../M80_Services/Random/Random.hpp"
#include "../../M90_Utilities/Math/MathUtilities.hpp"
#include "../../M90_Utilities/Assert/Assert.hpp"
#include <algorithm>
#include <random>

ApplicationSelectionStates::ApplicationSelectionStates(
	States& states,
    ApplicationsManager& applicationsManager,
    Random& random)
:
	_states(states),
    _applicationsManager(applicationsManager),
    _random(random)
{
}

std::vector<Application::ETag> ApplicationSelectionStates::GetSelectableTags() const
{
    return _selectableTags;
}

std::vector<uint16_t> ApplicationSelectionStates::GetSelectableApplicationIndices() const
{
    return _selectableApplicationIndices;
}

uint16_t ApplicationSelectionStates::GetSelectedApplicationIndex() const
{
    return _applicationsManager.GetNvsSettings().GetLastSelectedApplicationIndex();
}

void ApplicationSelectionStates::SetSelectedApplicationIndex(
    uint16_t index)
{
    _applicationsManager.GetNvsSettings().SetLastSelectedApplicationIndex(index);
}

ApplicationSelectionStates::EViewMode ApplicationSelectionStates::GetSelectedViewMode() const
{
    return (EViewMode)_applicationsManager.GetNvsSettings().GetLastSelectedViewModeIndex();
}

void ApplicationSelectionStates::SetSelectedViewMode(
    EViewMode selectedViewMode)
{
    _applicationsManager.GetNvsSettings().SetLastSelectedViewModeIndex((uint8_t) selectedViewMode);
}

void ApplicationSelectionStates::ModifySelectedViewMode(
    bool increase)
{
    auto count = static_cast<int>(EViewMode::Last);
    auto applicationViewModeIndex = static_cast<uint8_t>(MathUtilities::WrapEnum(
        GetSelectedViewMode(), increase ? 1 : -1, count));

    _applicationsManager.GetNvsSettings().SetLastSelectedViewModeIndex(applicationViewModeIndex);
}

uint8_t ApplicationSelectionStates::GetSelectedTagIndex() const
{
    return _applicationsManager.GetNvsSettings().GetLastSelectedTagIndex();
}

void ApplicationSelectionStates::SetSelectedTagIndex(
    uint8_t selectedTagIndex)
{
    _applicationsManager.GetNvsSettings().SetLastSelectedTagIndex(selectedTagIndex);
}

Application::EType ApplicationSelectionStates::GetSelectedApplicationType() const
{
    return (Application::EType)
        _applicationsManager.GetNvsSettings().GetLastSelectedApplicationTypeIndex();
}

void ApplicationSelectionStates::SetSelectedApplicationType(
    Application::EType applicationType)
{
    _applicationsManager.GetNvsSettings().SetLastSelectedApplicationTypeIndex(
        static_cast<uint8_t>(applicationType));
}

void ApplicationSelectionStates::ModifySelectedApplicationType(
    bool increase)
{
    auto count = static_cast<int>(Application::EType::Last);
    auto applicationTypeIndex = static_cast<uint8_t>(MathUtilities::WrapEnum(
        GetSelectedApplicationType(), increase ? 1 : -1, count));

    _applicationsManager.GetNvsSettings().SetLastSelectedApplicationTypeIndex(applicationTypeIndex);
}

void ApplicationSelectionStates::FilterSelectableTags()
{
    _selectableTags.clear();
    for (uint16_t applicationIndex = 0; applicationIndex < ApplicationsInfo::GetNrOfApplications(); 
        applicationIndex++)
    {
        FilterSelectableTagFromApplicationIndex(applicationIndex);
    }
}

void ApplicationSelectionStates::FilterSelectableTagFromApplicationIndex(
    uint16_t applicationIndex)
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

void ApplicationSelectionStates::FilterSelectableApplications()
{
    _selectableApplicationIndices.clear();
    for (uint16_t applicationIndex = 0; applicationIndex < ApplicationsInfo::GetNrOfApplications();
        applicationIndex++)
    {
        if (const std::string_view menuName(MenuApplication::NAME.data(), 
            MenuApplication::NAME.size());
            ApplicationsInfo::GetNameByIndex(applicationIndex) == menuName)
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
        using enum EViewMode;
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
            FilterSelectableApplicationsByTags(applicationIndex, append);
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

void ApplicationSelectionStates::FilterSelectableApplicationsByTags(
    uint16_t applicationIndex, 
    bool& append)
{
    for (IApplication::ETag tag : ApplicationsInfo::GetTagsByIndex(applicationIndex))
    {
        if (tag == _selectableTags[GetSelectedTagIndex()])
        {
            append = true;
            break;
        }
    }
}

void ApplicationSelectionStates::SortSelectableApplications()
{
    switch (GetSelectedViewMode())
    {
    using enum EViewMode;
    case Recent: // fallthrough
    case Alphabetic: // fallthrough
    case Favorites: // fallthrough
    case New: // fallthrough
    case Tag: // fallthrough
        std::sort(
            _selectableApplicationIndices.begin(),
            _selectableApplicationIndices.end(),
            [](uint16_t a, uint16_t b)
            {
                return 
                    ApplicationsInfo::GetNameByIndex(a) >
                    ApplicationsInfo::GetNameByIndex(b);
            }
        );
        break;

    case MostUsed:
    {
        std::sort(
            _selectableApplicationIndices.begin(),
            _selectableApplicationIndices.end(),
            [](uint16_t a, uint16_t b)
            {
                return 
                    ApplicationsInfo::GetNrOfStartsByIndex(a) >
                    ApplicationsInfo::GetNrOfStartsByIndex(b);
            }
        );
    }
    break;

    case Random:
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

    default:
        Assert::Fail(Types::ETaskId::ApplicationsTask, "Unknown tag");
        break;
    }
}
