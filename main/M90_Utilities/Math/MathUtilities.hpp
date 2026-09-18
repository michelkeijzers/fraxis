#pragma once

#include <cstdint>
#include <type_traits> 

class MathUtilities
{
public:
    static int32_t Wrap(
        uint32_t index,
        uint32_t max_value);

    template<typename TEnum>
    static TEnum WrapEnum(
        TEnum value,
        int delta, 
        int count)
    {
        auto v = static_cast<int>(value);
        v = (v + delta + count) % count;
        return static_cast<TEnum>(v);
    };

    template<typename T, typename U, typename V>
    static constexpr auto Clamp(T value, U minValue, V maxValue)
    {
        using R = std::common_type_t<T, U, V>;
        auto v = static_cast<R>(value);
        auto minV = static_cast<R>(minValue);
        auto maxV = static_cast<R>(maxValue);

        if (v < minV)
            return minV;

        if (v > maxV)
            return maxV;

        return v;
    }
};
