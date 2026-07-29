#pragma once

#define ASSERTS_ENABLED 1

#include <string>
#include <list>
#include <cassert>
#include <unordered_set>
#include <source_location>
#include <cstdlib>

class Assert
{
public:
#ifdef ASSERTS_ENABLED
    static void Fail(std::string_view message, std::source_location loc = std::source_location::current());
    static void IsTrue(bool condition, std::string_view message);
    static void IsFalse(bool condition, std::string_view message);
    static void IsNotNullptr(void* pointer, std::string_view variableName); 
    static void Equals(int real, int expected, std::string_view variableName);
    static void NotEquals(int real, int expected, std::string_view variableName);
    static void IsNot0(int real, std::string_view variableName);
    static void IsEsp32Pin(uint8_t pin, std::string_view message);

    template<typename T, typename MinT, typename MaxT>
    static void IsBetween(
        const T& value, const MinT& minValueIncluding, const MaxT& maxValueExcluding, const std::string_view& message)
    {
        T minT = static_cast<T>(minValueIncluding);
        T maxT = static_cast<T>(maxValueExcluding);

        IsTrue((value >= minT) && (value < maxT), message);
    }

    template<typename Container>
    static void AreUnique(const Container& values, std::string_view message)
    {
        using T = typename Container::value_type;
        std::unordered_set<T> seen;
        for (const T& v : values)
        {
            Assert::IsTrue(seen.count(v) == 0, message);
            seen.insert(v);
        }
    };
    
#else 
    static inline void Fail(std::string_view message) {}
    static inline void IsTrue(bool condition, std::string_view message) {}
    static inline void IsFalse(bool condition, std::string_view message) {}
    static inline void IsNotNullptr(void* pointer, std::string_view variableName) {}
    static inline void Equals(int real, int expected, std::string_view variableName) {}
    static inline void NotEquals(int real, int expected, std::string_view variableName) {}
    static inline void Not0(int real, std::string_view variableName) {}

    template<typename Container>
    static void AreUnique(const Container& values) {}
#endif

    static void Halt();
};
