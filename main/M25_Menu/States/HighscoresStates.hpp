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

    HighscoresStates(const HighscoresStates&) = delete;
    HighscoresStates& operator=(const HighscoresStates&) = delete;
    HighscoresStates(HighscoresStates&&) = delete;
    HighscoresStates& operator=(HighscoresStates&&) = delete;

    ~HighscoresStates() = default;

private:
    States& _states;
    ApplicationsManager& _applicationsManager;
};
