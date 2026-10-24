#pragma once

#include <span>

class ArrayUtilities
{
public:
    /// @brief Find first index of an item, or -1 if not found
    /// @tparam T 
    /// @param arr 
    /// @param length 
    /// @param value 
    /// @return 
    template<typename T>
    static int FindFirstIndexOf(
        std::span<const T> arr, 
        const T& value)
    {
        for (int i = 0; i < arr.size(); ++i)
        {
            if (arr[i] == value)
            {
                return i;
            }
        }
        return -1;
    }

    /// @brief Find first index not equal to an item, or -1 if not found
    template<typename T>
    static int FindFirstNonEqual(
        const T* a,
        const T* b,
        int length)
    {
        for (int i = 0; i < length; ++i)
        {
            if (!(a[i] == b[i]))
            {
                return i;
            }
        }
        return -1;
    }  

    /// @brief Find first index of an item in two arrays, or -1 if not found
    template<typename T, size_t N>
    static int FindFirstNonEqual(
        const std::array<T, N>& a,
        const std::array<T, N>& b)
    {
        for (size_t i = 0; i < N; ++i)
        {
            if (!(a[i] == b[i]))
            {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

    /// @brief Count the different items in two lists.
    template<typename T>
    static int CountDifferent(
        const T* a,
        const T* b, 
        int length)
{
    int count = 0;
    for (int i = 0; i < length; ++i)
    {
        if (!(a[i] == b[i]))
        {
            ++count;
        }
    }
    return count;
}
};
