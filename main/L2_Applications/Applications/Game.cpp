#include "Game.hpp"
#include "../../L1_Composition/Context/Context.hpp"
#include "../../L2_Applications/ApplicationsManager.hpp"
#include "../../L3_Messages/Types.hpp"
#include "../../L8_Services/Random/Random.hpp"
#include "../../L9_Utilities/Time/TimeUtilities.hpp" 

Game::Game(
    Context& context, 
    ApplicationsManager& applicationsManager) 
:   
    Application(context, applicationsManager)
{
}

const Highscores& Game::GetHighscores() const
{
    return _highscores;
}
