#pragma once

#define ASSERTS_ENABLED 1

#include "../Log/Log.hpp"
#include "../../L3_Messages/Types.hpp"
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
        Types::ETaskId taskId,
        std::string_view message = "", 
        std::source_location loc = std::source_location::current());

    static void IsTrue(
        Types::ETaskId taskId,
        bool condition,
        std::string_view message = "", 
        std::source_location loc = std::source_location::current());

    static void IsFalse(
        Types::ETaskId taskId,
        bool condition, 
        std::string_view message = "", 
        std::source_location loc = std::source_location::current());

    static void IsNotNullptr(
        Types::ETaskId taskId,
        void* pointer, 
        std::string_view variableName = "", 
        std::source_location loc = std::source_location::current());

    static void IsEsp32Pin(
        Types::ETaskId taskId,
        uint8_t pin, 
        std::string_view message = "", 
        std::source_location loc = std::source_location::current());

    template<typename T, typename U>
    static void Equals(
        Types::ETaskId taskId,
        const T& real,
        const U& expected,
        std::string_view variableName,
        std::source_location loc = std::source_location::current())
    {
        if (!(real == expected))
        {
            Log::Text(taskId, std::string(loc.file_name()) + ":" + std::to_string(loc.line())); // NOSONAR ESP32 has unrealiable std::format
            Log::Text(taskId, std::string(ASSERT) + std::string(variableName) +
                        " is expected to be " + std::to_string(expected) +
                        " but is " + std::to_string(real) + "!");
            Halt();
        }
    }

    template<typename T, typename U>
    static void NotEquals(
        Types::ETaskId taskId,
        const T& real, 
        const U& expected,
        std::string_view variableName,
        std::source_location loc = std::source_location::current())
    {
        if (real == expected)
        {
            Log::Text(taskId, std::string(loc.file_name()) + ":" + std::to_string(loc.line())); // NOSONAR ESP32 has unrealiable std::format
            Log::Text(taskId, std::string(ASSERT) + std::string(variableName) +
                        " is not expected to be " + std::to_string(expected) + "!");
            Halt();
        }
    }

    template<typename T>
    static void IsNot0(
        Types::ETaskId taskId,
        const T& real,
        std::string_view variableName,
        std::source_location loc = std::source_location::current())
    {
        NotEquals(taskId, real, static_cast<T>(0), variableName, loc);
    }

    template<typename T, typename MinT, typename MaxT>
    static void IsBetween(
        Types::ETaskId taskId,
        const T& value, 
        const MinT& minValueIncluding,
        const MaxT& maxValueExcluding, 
        const std::string_view& message = "", 
        std::source_location loc = std::source_location::current())
    {
        auto minT = static_cast<T>(minValueIncluding);
        auto maxT = static_cast<T>(maxValueExcluding);

        IsTrue(taskId, (value >= minT) && (value < maxT), message);
    }

    template<typename Container>
    static void AreUnique(
        Types::ETaskId taskId,
        const Container& values,
        std::string_view message = "", 
        std::source_location loc = std::source_location::current())
    {
        using T = typename Container::value_type;
        std::unordered_set<T> seen;
        for (const T& v : values)
        {
            Assert::IsTrue(taskId, seen.count(v) == 0, message);
            seen.insert(v);
        }
    };
    
#else 
    static inline void Fail(
        Types::ETaskId taskId,
        std::string_view message = "", 
        std::source_location loc = std::source_location::current()) 
    {
    }

    static inline void IsTrue(
        Types::ETaskId taskId,
        bool condition, 
        std::string_view message = "", 
        std::source_location loc = std::source_location::current()) 
    {
    }

    static inline void IsFalse(
        Types::ETaskId taskId,
        bool condition, 
        std::string_view message = "", 
        std::source_location loc = std::source_location::current()) 
    {
    }


    static inline void IsNotNullptr(
        Types::ETaskId taskId,
        void* pointer, 
        std::string_view variableName = "", 
        std::source_location loc = std::source_location::current()) 
    {
    }

    static inline void Equals(
        Types::ETaskId taskId,
        int real,
        int expected, std::string_view variableName = "", 
        std::source_location loc = std::source_location::current()) 
    {
    }

    static inline void NotEquals(
        Types::ETaskId taskId,
        int real,
        int expected, std::string_view variableName = "", 
        std::source_location loc = std::source_location::current()) 
    {
    }
    static inline void Not0(
        Types::ETaskId taskId,
        int real,
        std::string_view variableName = "", 
        std::source_location loc = std::source_location::current()) 
    {
    }

    template<typename T, typename U>
    static void NotEquals(
        Types::ETaskId taskId,
        const T& real, 
        const U& expected,
        std::string_view variableName,
        std::source_location loc = std::source_location::current()) 
    {
    }

    template<typename T>
    static void IsNot0(
        Types::ETaskId taskId,
        const T& real,
        std::string_view variableName,
        std::source_location loc = std::source_location::current()) 
    {
    }

    template<typename T, typename MinT, typename MaxT>
    static void IsBetween(
        Types::ETaskId taskId,
        const T& value, 
        const MinT& minValueIncluding, 
        const MaxT& maxValueExcluding, 
        const std::string_view& message = "", 
        std::source_location loc = std::source_location::current()) 
    {
    }

    template<typename T, typename MinT, typename MaxT>
    static inline void IsBetween(
        Types::ETaskId taskId,
        const T& value,
        const MinT& minValueIncluding,
        const MaxT& maxValueExcluding, 
        const std::string_view& message = "", 
        std::source_location loc = std::source_location::current()) 
    {
    }

    template<typename Container>
    static inline void AreUnique(
        Types::ETaskId taskId,
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
