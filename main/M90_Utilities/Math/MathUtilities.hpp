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
        auto castedValue = static_cast<int>(value);
        castedValue = (castedValue + delta + count) % count;
        return static_cast<TEnum>(castedValue);
    };

    template<typename T, typename U, typename V>
    static constexpr auto Clamp(T value, U minValue, V maxValue)
    {
        using R = std::common_type_t<T, U, V>;
        auto castedValue = static_cast<R>(value);
        auto minV = static_cast<R>(minValue);
        auto maxV = static_cast<R>(maxValue);

        if (castedValue < minV)
        {
            return minV;
        }

        if (castedValue > maxV)
        {
            return maxV;
        }

        return castedValue;
    }
};
