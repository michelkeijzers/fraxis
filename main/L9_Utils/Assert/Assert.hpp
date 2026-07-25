#pragma once

#include <string>

class Assert
{
public:
    static void IsTrue(bool condition, std::string message);
    static void IsFalse(bool condition, std::string message);
    static void IsNotNullptr(bool condition, std::string variableName); 
    static void Equals(int real, int expected, std::string variableName);
};
