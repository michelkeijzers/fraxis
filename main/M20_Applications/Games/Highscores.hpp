#pragma once

#include <array>
#include <cstdint>
#include "Highscore.hpp"

class Highscore;

class Highscores
{
public:
    static constexpr uint8_t MAX_NR_OF_ENTRIES = 25;

    Highscores();

    const std::array<Highscore, MAX_NR_OF_ENTRIES>& GetEntries() const;

private:
    std::array<Highscore, MAX_NR_OF_ENTRIES> _entries;
};
