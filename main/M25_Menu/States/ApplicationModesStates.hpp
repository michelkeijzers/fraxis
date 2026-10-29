#pragma once

#include "../../M20_Applications/Applications/Application.hpp"
#include <stdint.h>
#include <vector>

class States;
class ApplicationsManager;

class ApplicationModesStates
{
public:
    ApplicationModesStates(
        States& states,
        ApplicationsManager& applicationsManager);

    ApplicationModesStates(const ApplicationModesStates&) = delete;
    ApplicationModesStates& operator=(const ApplicationModesStates&) = delete;
    ApplicationModesStates(ApplicationModesStates&&) = delete;
    ApplicationModesStates& operator=(ApplicationModesStates&&) = delete;

    ~ApplicationModesStates() = default;

    enum class EApplicationMode : uint8_t
    {
        Start,
        Running,
        Resume,
        Quit,
        Settings,
        Highscores,
        MakeFavorite,
        ResetSettings,
        ResetHighscores,
        ResetNrOfTimesStarted,
        ResetLastStartTime,
        Last
    };

    static constexpr uint8_t NR_OF_APPLICATION_MODES = static_cast<uint8_t>(EApplicationMode::Last);

    [[nodiscard]] EApplicationMode GetSelectedApplicationMode() const;
    void SetSelectedApplicationMode(
        EApplicationMode applicationMode);

    [[nodiscard]] std::vector<EApplicationMode> GetSelectableApplicationModes() const;

    void ExecuteS040State();

    void OnJoystickUp();
    void OnJoystickDown();

    void ProcessApplicationMode();

private:
    void FilterSelectableApplicationModes();

    States& _states;
    ApplicationsManager& _applicationsManager;

    std::vector<EApplicationMode> _selectableApplicationModes;
    EApplicationMode _selectedApplicationMode;
};
