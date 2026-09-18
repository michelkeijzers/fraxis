#pragma once

#include <cstdint>
#include <string_view>

class Highscore
{
public:
    static constexpr uint8_t MAX_NAME_LENGTH = 8;

    Highscore();
    ~Highscore() = default;
    
    std::string_view GetName() const;
    uint32_t GetScore() const;

    void Set(
        std::string_view name,
        uint32_t score);

private:
    char _name[MAX_NAME_LENGTH];
    uint32_t _score;
};
