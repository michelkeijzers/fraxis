#include "HighscoresStates.hpp"
#include "../../M20_Applications/Applications/Application.hpp"
#include "../../M20_Applications/ApplicationsManager.hpp"
#include <cstdint>

HighscoresStates::HighscoresStates(
    States& states,
    ApplicationsManager& applicationsManager)
    :
    _states(states),
    _applicationsManager(applicationsManager)
{
}
