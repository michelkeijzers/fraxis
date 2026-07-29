#pragma once

#include <cstdint>

class Color
{
public:
    Color();
    Color(uint8_t red, uint8_t green, uint8_t blue);
    ~Color();

    void Set(uint8_t red, uint8_t green, uint8_t blue);
    void SetRed(uint8_t red);
    void SetGreen(uint8_t green);
    void SetBlue(uint8_t blue);

    void Get(uint8_t& red, uint8_t& green, uint8_t& blue);
    uint8_t GetRed() const;
    uint8_t GetGreen() const;
    uint8_t GetBlue() const;

    /// @brief Returns the sum of all color components.
    uint16_t GetSum() const;

    /// @brief Adjusts the brightness.
    /// @param brightness ratio of the new brightness
    void AdjustBrightness(uint8_t brightness);

    void operator=(const Color& other);
    bool operator==(const Color& other) const;
    bool operator!=(const Color& other) const;
    void operator+=(const Color& other);
    void operator-=(const Color& other);

private:
    uint8_t _red;
    uint8_t _green;
    uint8_t _blue;
};
