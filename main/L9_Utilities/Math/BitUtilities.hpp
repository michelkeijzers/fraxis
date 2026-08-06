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
    static T SetBit(T value, uint8_t bitNumber, bool on)
    {
        T mask = T(1) << bitNumber;
        return on ? (value | mask) : (value & ~mask);
    }

    /// @brief  As SetBit, but non templated
    static uint16_t SetBit(uint16_t value, uint8_t bitNumber, bool on)
    {
        if (on)
            return value | (uint16_t(1) << bitNumber);
        else
            return value & ~(uint16_t(1) << bitNumber);
    }

    /// @brief  As SetBit, but non templated
    static uint8_t SetBit(uint8_t value, uint8_t bitNumber, bool on)
    {
        if (on)
            return value | (uint8_t(1) << bitNumber);
        else
            return value & ~(uint8_t(1) << bitNumber);
    }

    template<typename T>
    static constexpr bool IsBitSet(T value, uint8_t bitNumber)
    {
        return (value & (1 << bitNumber)) != 0;
    }
};
