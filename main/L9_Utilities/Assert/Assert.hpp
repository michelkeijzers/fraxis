#pragma once

#define ASSERTS_ENABLED 1

#include "../Log/Log.hpp"
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
    static void Fail(
        std::string_view message = "", 
        std::source_location loc = std::source_location::current());
    static void IsTrue(
        bool condition,
        std::string_view message = "", 
        std::source_location loc = std::source_location::current());
    static void IsFalse(
        bool condition, 
        std::string_view message = "", 
        std::source_location loc = std::source_location::current());
    static void IsNotNullptr(
        void* pointer, 
        std::string_view variableName = "", 
        std::source_location loc = std::source_location::current());
    static void IsEsp32Pin(uint8_t pin, 
        std::string_view message = "", 
        std::source_location loc = std::source_location::current());

    template<typename T, typename U>
    static void Equals(
        const T& real,
        const U& expected,
        std::string_view variableName,
        std::source_location loc = std::source_location::current())
    {
        if (!(real == expected))
        {
            Log::Text(std::string(loc.file_name()) + ":" + std::to_string(loc.line())); // NOSONAR ESP32 has unrealiable std::format
            Log::Text(std::string(ASSERT) + std::string(variableName) +
                        " is expected to be " + std::to_string(expected) +
                        " but is " + std::to_string(real) + "!");
            Halt();
        }
    }

    template<typename T, typename U>
    static void NotEquals(
        const T& real, 
        const U& expected,
        std::string_view variableName,
        std::source_location loc = std::source_location::current())
    {
        if (real == expected)
        {
            Log::Text(std::string(loc.file_name()) + ":" + std::to_string(loc.line())); // NOSONAR ESP32 has unrealiable std::format
            Log::Text(std::string(ASSERT) + std::string(variableName) +
                        " is not expected to be " + std::to_string(expected) + "!");
            Halt();
        }
    }

    template<typename T>
    static void IsNot0(
        const T& real,
        std::string_view variableName,
        std::source_location loc = std::source_location::current())
    {
        NotEquals(real, static_cast<T>(0), variableName, loc);
    }

    template<typename T, typename MinT, typename MaxT>
    static void IsBetween(
        const T& value, 
        const MinT& minValueIncluding,
        const MaxT& maxValueExcluding, 
        const std::string_view& message = "", 
        std::source_location loc = std::source_location::current())
    {
        auto minT = static_cast<T>(minValueIncluding);
        auto maxT = static_cast<T>(maxValueExcluding);

        IsTrue((value >= minT) && (value < maxT), message);
    }

    template<typename Container>
    static void AreUnique(
        const Container& values,
        std::string_view message = "", 
        std::source_location loc = std::source_location::current())
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
    static inline void Fail(
        std::string_view message = "", 
        std::source_location loc = std::source_location::current()) 
    {
    }

    static inline void IsTrue(
        bool condition, 
        std::string_view message = "", 
        std::source_location loc = std::source_location::current()) 
    {
    }

    static inline void IsFalse(
        bool condition, 
        std::string_view message = "", 
        std::source_location loc = std::source_location::current()) 
    {
    }


    static inline void IsNotNullptr(
        void* pointer, 
        std::string_view variableName = "", 
        std::source_location loc = std::source_location::current()) 
    {
    }

    static inline void Equals(
        int real,
        int expected, std::string_view variableName = "", 
        std::source_location loc = std::source_location::current()) 
    {
    }

    static inline void NotEquals(
        int real,
        int expected, std::string_view variableName = "", 
        std::source_location loc = std::source_location::current()) 
    {
    }
    static inline void Not0(
        int real,
        std::string_view variableName = "", 
        std::source_location loc = std::source_location::current()) 
    {
    }

    template<typename T, typename U>
    static void NotEquals(
        const T& real, 
        const U& expected,
        std::string_view variableName,
        std::source_location loc = std::source_location::current()) 
    {
    }

    template<typename T>
    static void IsNot0(
        const T& real,
        std::string_view variableName,
        std::source_location loc = std::source_location::current()) 
    {
    }

    template<typename T, typename MinT, typename MaxT>
    static void IsBetween(
        const T& value, 
        const MinT& minValueIncluding, 
        const MaxT& maxValueExcluding, 
        const std::string_view& message = "", 
        std::source_location loc = std::source_location::current()) 
    {
    }

    template<typename T, typename MinT, typename MaxT>
    static inline void IsBetween(
        const T& value,
        const MinT& minValueIncluding,
        const MaxT& maxValueExcluding, 
        const std::string_view& message = "", 
        std::source_location loc = std::source_location::current()) 
    {
    }

    template<typename Container>
    static inline void AreUnique(
        const Container& values,
        std::string_view message = "", 
        std::source_location loc = std::source_location::current()) 
    {
    }
#endif

    static void Halt();

private:
    static std::string ASSERT;
};
