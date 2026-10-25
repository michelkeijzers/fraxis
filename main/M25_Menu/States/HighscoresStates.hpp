#pragma once

#include <cstdint>

class States;
class ApplicationsManager;

class HighscoresStates
{
public:
    HighscoresStates(
        States& states,
        ApplicationsManager& applicationsManager);
    ~HighscoresStates() = default;

private:
    States& _states;
    ApplicationsManager& _applicationsManager;
};
