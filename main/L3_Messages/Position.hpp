#pragma once

#include <cstdint>

/// @brief Led strips position.
/// @details By default, horizontal oriental is default, and coordinate (0,0) is at the left bottom.
/// The most top right pixel in horizontal orientation is (71, 4).
/// In case the orientation is vertical, the most top right coordinate is (4, 71).
class Position
{
public:
    Position();
    Position(uint8_t x, uint8_t y);
    ~Position();

    void Set(uint8_t x, uint8_t y);
    void SetX(uint8_t x);
    void SetY(uint8_t y);

    void Get(uint8_t& x, uint8_t& y);
    uint8_t GetX() const;
    uint8_t GetY() const;

    void operator=(const Position& other);
    bool operator==(const Position& other) const;
    bool operator!=(const Position& other) const;
    void operator+=(const Position& other);
    void operator-=(const Position& other);

private:
    uint8_t _x;
    uint8_t _y;
};
