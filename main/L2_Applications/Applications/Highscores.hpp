#pragma once 

#include "Highscore.hpp"
#include <array>

class Highscores
{
public:
    static constexpr uint8_t MAX_NR_OF_ENTRIES = 25;

    Highscores();
    ~Highscores() = default;

    const uint8_t GetNrOfEntries() const;
    const std::array<Highscore, MAX_NR_OF_ENTRIES> GetEntries() const;

private:
    uint8_t _nrOfEntries;
    std::array<Highscore, MAX_NR_OF_ENTRIES> _entries;
};
