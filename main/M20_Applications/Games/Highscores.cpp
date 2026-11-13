#include "Highscores.hpp"

Highscores::Highscores()
:
    _entries{}
{
}

const std::array<Highscore, Highscores::MAX_NUMBER_OF_ENTRIES>& Highscores::GetEntries() const
{
    return _entries;
}
