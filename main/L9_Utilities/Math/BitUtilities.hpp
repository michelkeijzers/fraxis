#pragma once

#include <cstdint>

class BitUtilities
{
public:
    /// @brief Sets a bit in a value
    /// @details Usage:
    /// uint16_t v16 = SetBit<uint16_t>(v16, 3, true);
    /// uint8_t  v8  = SetBit<uint8_t>(v8, 1, false);

    template<typename T>
    static T SetBit(T value, uint8_t bit, bool on)
    {
        T mask = T(1) << bit;
        return on ? (value | mask) : (value & ~mask);
    }

    /// @brief  As SetBit, but non templated
    static uint16_t SetBit(uint16_t value, uint8_t bit, bool on)
    {
        if (on)
            return value | (uint16_t(1) << bit);
        else
            return value & ~(uint16_t(1) << bit);
    }

    /// @brief  As SetBit, but non templated
    static uint8_t SetBit(uint8_t value, uint8_t bit, bool on)
    {
        if (on)
            return value | (uint8_t(1) << bit);
        else
            return value & ~(uint8_t(1) << bit);
    }

    template<typename T>
    constexpr bool TestBit(T value, uint8_t bit)
    {
        return (value & BitMask<T>(bit)) != 0;
    }


};
