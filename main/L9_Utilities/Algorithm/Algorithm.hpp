#pragma once

class Algorithm
{
public:
    template<typename T>
    static void swap(T& a, T& b)
    {
        T temp = a;
        a = b;
        b = temp;
    }
};
