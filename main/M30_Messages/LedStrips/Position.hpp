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

    Position(
        uint8_t xPosition,
        uint8_t yPosition);

    ~Position() = default;

    Position(
        const Position&) = default;
    Position& operator=(
        const Position&) = default;
    Position(
        Position&&) noexcept = default;
    Position& operator=(
        Position&&) noexcept = default;

    void Set(
        uint8_t xPosition,
        uint8_t yPosition);
    void SetX(
        uint8_t xPosition);
    void SetY(
        uint8_t yPosition);

    void Get(
        uint8_t& xPosition,
        uint8_t& yPosition) const;

    [[nodiscard]] uint8_t& GetX();
    [[nodiscard]] uint8_t& GetY();
    [[nodiscard]] const uint8_t& GetX() const;
    [[nodiscard]] const uint8_t& GetY() const;

private:
    uint8_t _xPosition;
    uint8_t _yPosition;
};
