#pragma once

class Algorithm
{
public:
    template<typename T>
    static void Swap(
        T& a, 
        T& b)
    {
        T temp = a;
        a = b;
        b = temp;
    }
};
