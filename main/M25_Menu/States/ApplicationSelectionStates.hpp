#pragma once

#include "../../M20_Applications/Applications/Application.hpp"
#include <cstdint>
#include <vector>

class States;
class ApplicationsManager;
class Random;

class ApplicationSelectionStates
{
public:
    ApplicationSelectionStates(
        States& states,
        ApplicationsManager& applicationsManager,
        Random& random);
    ~ApplicationSelectionStates() = default;

    enum class EViewMode {
        Recent,
        MostUsed,
        Favorites,
        Alphabetic,
        Tag,
        New,
        Random,
        Last
    };

    static constexpr uint8_t NR_OF_VIEW_MODES = static_cast<uint8_t>(EViewMode::Last);

    uint16_t GetSelectedApplicationIndex() const;
    void SetSelectedApplicationIndex(
        uint16_t selectedApplicationIndex);

    EViewMode GetSelectedViewMode() const;
    void SetSelectedViewMode(
        EViewMode selectedViewMode);
    void SetSelectedViewMode(
        bool increase);

    uint8_t GetSelectedTagIndex() const;
    void SetSelectedTagIndex(
        uint8_t selectedTagIndex);

    std::vector<Application::ETag> GetSelectableTags() const;

    Application::EType GetSelectedApplicationType() const;
    void SetSelectedApplicationType(
        Application::EType applicationType);
    void SetSelectedApplicationType(
        bool increase);

    void FilterSelectableTags();
    void FilterSelectableApplications();

    void FilterTag(
        IApplication::ETag tag);

    std::vector<uint16_t> GetSelectableApplicationIndices() const;
    void SortSelectableApplications();

private:
    States& _states;
    ApplicationsManager& _applicationsManager;

    std::vector<uint16_t> _selectableApplicationIndices;
    std::vector<Application::ETag> _selectableTags;

    Random& _random;
};
