#pragma once

#include <cstdint>
#include <type_traits> 

class MathUtilities
{
public:
template<typename T>
    static T Wrap(
        T index,
        T max_value)
    {
        return (index % max_value + max_value) % max_value;
    }

    template<typename TEnum>
    static TEnum WrapEnum(
        TEnum value,
        int32_t delta, 
        uint32_t count)
    {
        int32_t wrapped = 
            (static_cast<int32_t>(value) + delta + 
            static_cast<int32_t>(static_cast<int32_t>(count))) % 
            static_cast<int32_t>(count);
        return static_cast<TEnum>(static_cast<uint32_t>(wrapped));
    };

    template<typename T, typename U, typename V>
    static constexpr auto Clamp(
        T value, 
        U minValue, 
        V maxValue)
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
