#include "Highscores.hpp"

Highscores::Highscores()
:
    _nrOfEntries(0),
    _entries{}
{
}

uint8_t Highscores::GetNrOfEntries() const
{
    return _nrOfEntries;
}

const std::array<Highscore, Highscores::MAX_NR_OF_ENTRIES>& Highscores::GetEntries() const
{
    return _entries;
}
