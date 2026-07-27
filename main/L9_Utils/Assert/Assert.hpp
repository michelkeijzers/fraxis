#pragma once

#include <string>

#define ASSERTS_ENABLED 1

class Assert
{
public:
#if ASSERTS_ENABLED
    static void IsTrue(bool condition, std::string message);
    static void IsFalse(bool condition, std::string message);
    static void IsNotNullptr(void* pointer, std::string variableName); 
    static void Equals(int real, int expected, std::string variableName);
#else 
    static inline void IsTrue(bool condition, std::string message) {}
    static inline void IsFalse(bool condition, std::string message) {}
    static inline void IsNotNullptr(void* pointer, std::string variableName) {}
    static inline void Equals(int real, int expected, std::string variableName) {}
#endif
};
