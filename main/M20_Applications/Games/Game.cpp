#include "Game.hpp"
#include "../../M10_Composition/Context/Context.hpp"
#include "../../M20_Applications/ApplicationsManager.hpp"
#include "../../M30_Messages/Types.hpp"

Game::Game(
    EApplicationId id,
    Context& context, 
    M90::String::IStringUtilities& stringUtilities,
    ApplicationsManager& applicationsManager) 
:   
    Application(id, context, stringUtilities, applicationsManager)
{
}

const Highscores& Game::GetHighscores() const
{
    return _highscores;
}
