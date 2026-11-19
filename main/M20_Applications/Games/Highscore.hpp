#pragma once

#include <cstdint>
#include <string_view>
#include <array>

class Highscore
{
public:
    static constexpr uint8_t MAX_NAME_LENGTH = 8;

    Highscore();

    ~Highscore() = default;
    
    std::string_view GetName() const;
  
    uint32_t GetScore() const;

private:
    std::array<char, MAX_NAME_LENGTH> _name;
    
    uint32_t _score;
};

// TODO
//void Highscore::Set(
//    std::string_view name,
//    uint32_t score)
//{
//    _stringUtilities.CopyToBuffer(name, _name.data(), MAX_NAME_LENGTH);
//    _score = score;
//}
//
