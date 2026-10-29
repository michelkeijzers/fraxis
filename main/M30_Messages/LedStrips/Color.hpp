#pragma once

#include <cstdint>

class Color
{
public:
    Color();

    Color(
        uint8_t red,
        uint8_t green,
        uint8_t blue);

    Color(const Color&) = default;
    Color& operator=(const Color&) = default;
    Color(Color&&) noexcept = default;
    Color& operator=(Color&&) noexcept = default;
    bool operator==(const Color& other) const = default; // != is automatically generated

    Color& operator+=(const Color& other);
    Color& operator-=(const Color& other);

    ~Color() = default;

    void Set(
        uint8_t red,
        uint8_t green,
        uint8_t blue);

    void SetRed(
        uint8_t red);

    void SetGreen(
        uint8_t green);

    void SetBlue(
        uint8_t blue);

    void Get(
        uint8_t& red,
        uint8_t& green,
        uint8_t& blue) const;

    [[nodiscard]] uint8_t GetRed() const;
    [[nodiscard]] uint8_t GetGreen() const;
    [[nodiscard]] uint8_t GetBlue() const;

    /// @brief Returns the sum of all color components.
    [[nodiscard]] uint16_t GetSum() const;

    /// @brief Adjusts the brightness.
    /// @param brightness ratio of the new brightness
    void AdjustBrightness(
        uint8_t brightness);

private:
    uint8_t _red;
    uint8_t _green;
    uint8_t _blue;
};
