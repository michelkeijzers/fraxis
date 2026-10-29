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

    ApplicationSelectionStates(const ApplicationSelectionStates&) = delete;
    ApplicationSelectionStates& operator=(const ApplicationSelectionStates&) = delete;
    ApplicationSelectionStates(ApplicationSelectionStates&&) = delete;
    ApplicationSelectionStates& operator=(ApplicationSelectionStates&&) = delete;

    ~ApplicationSelectionStates() = default;

    enum class EViewMode : uint8_t
    {
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

    [[nodiscard]] uint16_t GetSelectedApplicationIndex() const;
    void SetSelectedApplicationIndex(
        uint16_t selectedApplicationIndex);

    [[nodiscard]] EViewMode GetSelectedViewMode() const;

    void SetSelectedViewMode(
        EViewMode selectedViewMode);
    void ModifySelectedViewMode(
        bool increase);

    [[nodiscard]] uint8_t GetSelectedTagIndex() const;
    void SetSelectedTagIndex(
        uint8_t selectedTagIndex);

    [[nodiscard]] std::vector<Application::ETag> GetSelectableTags() const;

    [[nodiscard]] Application::EType GetSelectedApplicationType() const;
    void SetSelectedApplicationType(
        Application::EType applicationType);
    void ModifySelectedApplicationType(
        bool increase);

    void FilterSelectableTags();

    void FilterSelectableApplications();

    void FilterTag(
        IApplication::ETag tag);

    [[nodiscard]] std::vector<uint16_t> GetSelectableApplicationIndices() const;
    void SortSelectableApplications();

private:
    void FilterSelectableTagFromApplicationIndex(
        uint16_t applicationIndex);

    void FilterSelectableApplicationsByTags(
        uint16_t applicationIndex,
        bool& append);
        
    States& _states;
    ApplicationsManager& _applicationsManager;

    std::vector<uint16_t> _selectableApplicationIndices;
    std::vector<Application::ETag> _selectableTags;

    Random& _random;
};
