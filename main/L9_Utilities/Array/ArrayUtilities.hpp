#pragma once

class ArrayUtilities
{
public:
    template<typename T>
    static int FindFirstIndexOf(
        const T* arr, 
        int length,
        const T& value)
    {
        for (int i = 0; i < length; ++i)
        {
            if (arr[i] == value)
            {
                return i;
            }
        }
        return -1;
    }

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
