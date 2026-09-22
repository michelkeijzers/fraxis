#pragma once

#include "Highscores.hpp"
#include "../Applications/Application.hpp"
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
