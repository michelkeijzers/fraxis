#include "Game.hpp"
#include "../../M10_Composition/Context/Context.hpp"
#include "../../M20_Applications/ApplicationsManager.hpp"
#include "../../M30_Messages/Types.hpp"
#include "../../M80_Services/Random/Random.hpp"
#include "../../M90_Utilities/Time/TimeUtilities.hpp" 

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
