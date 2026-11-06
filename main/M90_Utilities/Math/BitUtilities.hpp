#pragma once

#include <cstdint>

class BitUtilities
{
public:
    /// @brief Sets a bit in a value
    template<typename T>
    static T SetBit(T value, uint8_t bitNumber, bool on)
    {
        T mask = T(1) << bitNumber;
        return on ? (value | mask) : (value & ~mask);
    }

    template<typename T>
    static constexpr bool IsBitSet(T value, uint8_t bitNumber)
    {
        return (value & (static_cast<uint64_t>(1) << bitNumber)) != 0;
    }
};
