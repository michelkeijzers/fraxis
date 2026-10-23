#include "Game.hpp"
#include "../../M10_Composition/Context/Context.hpp"
#include "../../M20_Applications/ApplicationsManager.hpp"
#include "../../M30_Messages/Types.hpp"
#include "../../M80_Services/Random/Random.hpp"
#include "../../M90_Utilities/Time/TimeUtilities.hpp" 

Game::Game(
    EApplicationId id,
    Context& context, 
    ApplicationsManager& applicationsManager) 
:   
    Application(id, context, applicationsManager)
{
}

const Highscores& Game::GetHighscores() const
{
    return _highscores;
}
1
1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890                    