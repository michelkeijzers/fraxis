#include "Highscores.hpp"

Highscores::Highscores()
:
    _entries{}
{
}

const std::array<Highscore, Highscores::MAX_NR_OF_ENTRIES>& Highscores::GetEntries() const
{
    return _entries;
}
