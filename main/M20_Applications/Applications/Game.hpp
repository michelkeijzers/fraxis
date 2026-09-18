#pragma once

#include "Application.hpp"
#include "Highscores.hpp"
#include <string>

class Context;
class ApplicationsManager;

class Game : public Application
{
public:
    Game(
        Context& context,
        ApplicationsManager& applicationsManager);
    ~Game() = default;

    const Highscores& GetHighscores() const;
    
private:
    const Highscores _highscores;
};
