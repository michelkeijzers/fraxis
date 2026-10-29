#pragma once

 // Use a macro, do not use constexpr
#define ASSERTS_ENABLED 1

#include "../Log/Log.hpp"
#include "../../M30_Messages/Types.hpp"
#include <string>
#include <list>
#include <cassert>
#include <unordered_set>
#include <source_location>
#include <cstdlib>

class Assert
{
public:
#if ASSERTS_ENABLED
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

    static void IsNotNullptr(
        Types::ETaskId taskId,
        const void* pointer,
        std::string_view variableName = "",
        std::source_location loc = std::source_location::current());

    static void IsEsp32Pin(
        Types::ETaskId taskId,
        uint8_t pin, 
        std::string_view message = "", 
        std::source_location loc = std::source_location::current());

    template<typename T>
    static std::string ToString(const T& value)
    {
        if constexpr (std::is_enum_v<T>)
        {
            return std::to_string(
                static_cast<std::underlying_type_t<T>>(value));
        }
        else if constexpr (std::is_arithmetic_v<T>)
        {
            return std::to_string(value);
        }
        else
        {
            return "<unsupported>";
        }
    }

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
            // NOLINTNEXTLINE(modernize-use-std-format)
            Log::Text(taskId, std::string(loc.file_name()) + ":" + std::to_string(loc.line()));
            Log::Text(taskId, std::string(ASSERT) + std::string(variableName) +
            " is expected to be " + ToString(expected) + " but is " + ToString(real) + "!");
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
            // NOLINTNEXTLINE(modernize-use-std-format)
            Log::Text(taskId, std::string(loc.file_name()) + ":" + 
                std::to_string(loc.line())); // NOSONAR ESP32 has unreliable std::format
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
        std::string_view message = "")
    {
        auto minT = static_cast<T>(minValueIncluding);
        auto maxT = static_cast<T>(maxValueExcluding);

        IsTrue(taskId, (value >= minT) && (value < maxT), message);
    }

    template<typename Container>
    static void AreUnique(
        Types::ETaskId taskId,
        const Container& values,
        std::string_view message = "")
    {
        using T = typename Container::value_type;
        std::unordered_set<T> seen;
        for (const T& value : values)
        {
            Assert::IsTrue(taskId, seen.count(value) == 0, message);
            seen.insert(value);
        }
    };
    
#else 
    static void Fail(
        Types::ETaskId taskId,
        std::string_view message = "", 
        std::source_location loc = std::source_location::current()) 
    {
    }

    static void IsTrue(
        Types::ETaskId taskId,
        bool condition, 
        std::string_view message = "", 
        std::source_location loc = std::source_location::current()) 
    {
    }

    static void IsFalse(
        Types::ETaskId taskId,
        bool condition, 
        std::string_view message = "", 
        std::source_location loc = std::source_location::current()) 
    {
    }

    static void IsNotNullptr(
        Types::ETaskId taskId,
        void* pointer, 
        std::string_view variableName = "", 
        std::source_location loc = std::source_location::current()) 
    {
    }

    static void Equals(
        Types::ETaskId taskId,
        // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
        int real,
        int expected, std::string_view variableName = "", 
        std::source_location loc = std::source_location::current()) 
    {
    }

    static void NotEquals(
        Types::ETaskId taskId,
        // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
        int real,
        int expected, std::string_view variableName = "", 
        std::source_location loc = std::source_location::current()) 
    {
    }
    static void Not0(
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

    template<typename Container>
    static void AreUnique(
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
