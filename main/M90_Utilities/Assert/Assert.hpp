// @file Assert.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#define ASSERTS_ENABLED 1

#include "../Log/Log.hpp"
#include "../../M30_Messages/Types.hpp"
#include <string>
#include <list>
#include <cassert>
#include <unordered_set>
#include <source_location>
#include <cstdlib>
#include <utility>

namespace M90::Assert
{
    class Assert
    {
    public:
#if ASSERTS_ENABLED
        [[noreturn]] static void Fail(
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
            if (!std::cmp_equal(real, expected))
            {
                // NOLINTNEXTLINE(modernize-use-std-format)
                M90::Log::Log::Text(
                    taskId,
                    std::string(loc.file_name()) + // NOSONAR S6185 format
                    ":" + std::to_string(loc.line()));
                M90::Log::Log::Text(taskId, std::string(ASSERT) + std::string(variableName) +
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
                M90::Log::Log::Text(
                    taskId,
                    std::string(loc.file_name()) + ":" + // NOSONAR S6185 format
                    std::to_string(loc.line()));
                M90::Log::Log::Text(taskId, std::string(ASSERT) + std::string(variableName) +
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
                Assert::IsTrue(taskId, !seen.contains(value), message);
                seen.insert(value);
            }
        };

#else 
        static void Fail(
            [[maybe_unused]] Types::ETaskId taskId,
            [[maybe_unused]] std::string_view message = "",
            [[maybe_unused]] std::source_location loc = std::source_location::current())
        {
            // Intentionally empty.
        }

        static void IsTrue(
            [[maybe_unused]] Types::ETaskId taskId,
            [[maybe_unused]] bool condition,
            [[maybe_unused]] std::string_view message = "",
            [[maybe_unused]] std::source_location loc = std::source_location::current())
        {
            // Intentionally empty.
        }

        static void IsFalse(
            [[maybe_unused]] Types::ETaskId taskId,
            [[maybe_unused]] bool condition,
            [[maybe_unused]] std::string_view message = "",
            [[maybe_unused]] std::source_location loc = std::source_location::current())
        {
            // Intentionally empty.
        }

        static void IsNotNullptr(
            [[maybe_unused]] Types::ETaskId taskId,
            [[maybe_unused]] void* pointer,
            [[maybe_unused]] std::string_view variableName = "",
            [[maybe_unused]] std::source_location loc = std::source_location::current())
        {
            // Intentionally empty.
        }

        static void IsNotNullptr(
            [[maybe_unused]] Types::ETaskId taskId,
            [[maybe_unused]] const void* pointer,
            [[maybe_unused]] std::string_view variableName = "",
            [[maybe_unused]] std::source_location loc = std::source_location::current())
        {
            // Intentionally empty.
        }

        static void IsEsp32Pin(
            [[maybe_unused]] Types::ETaskId taskId,
            [[maybe_unused]] uint8_t pin,
            [[maybe_unused]] std::string_view message = "",
            [[maybe_unused]] std::source_location loc = std::source_location::current())
        {
            // Intentionally empty.
        }

        static void Equals(
            [[maybe_unused]] Types::ETaskId taskId,
            // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
            [[maybe_unused]] int real,
            [[maybe_unused]] int expected, 
            [[maybe_unused]] std::string_view variableName = "",
            [[maybe_unused]] std::source_location loc = std::source_location::current())
        {
            // Intentionally empty.
        }

        static void NotEquals(
            [[maybe_unused]] Types::ETaskId taskId,
            // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
            [[maybe_unused]] int real,
            [[maybe_unused]] int expected, 
            [[maybe_unused]] std::string_view variableName = "",
            [[maybe_unused]] std::source_location loc = std::source_location::current())
        {
            // Intentionally empty.
        }

        static void Not0(
            [[maybe_unused]] Types::ETaskId taskId,
            [[maybe_unused]] int real,
            [[maybe_unused]] std::string_view variableName = "",
            [[maybe_unused]] std::source_location loc = std::source_location::current())
        {
            // Intentionally empty.
        }

        template<typename T, typename U>
        static void NotEquals(
            [[maybe_unused]] Types::ETaskId taskId,
            [[maybe_unused]] const T& real,
            [[maybe_unused]] const U& expected,
            [[maybe_unused]] std::string_view variableName,
            [[maybe_unused]] std::source_location loc = std::source_location::current())
        {
            // Intentionally empty.
        }

        template<typename T>
        static void IsNot0(
            [[maybe_unused]] Types::ETaskId taskId,
            [[maybe_unused]] const T& real,
            [[maybe_unused]] std::string_view variableName,
            [[maybe_unused]] std::source_location loc = std::source_location::current())
        {
            // Intentionally empty.
        }

        template<typename T, typename MinT, typename MaxT>
        static void IsBetween(
            [[maybe_unused]] Types::ETaskId taskId,
            [[maybe_unused]] const T& value,
            [[maybe_unused]] const MinT& minValueIncluding,
            [[maybe_unused]] const MaxT& maxValueExcluding,
            [[maybe_unused]] const std::string_view& message = "",
            [[maybe_unused]] std::source_location loc = std::source_location::current())
        {
            // Intentionally empty.
        }

        template<typename Container>
        static void AreUnique(
            [[maybe_unused]] Types::ETaskId taskId,
            [[maybe_unused]] const Container& values,
            [[maybe_unused]] std::string_view message = "",
            [[maybe_unused]] std::source_location loc = std::source_location::current())
        {
            // Intentionally empty.
        }
#endif

        [[noreturn]] static void Halt();

    private:
        static constexpr std::string_view ASSERT = "ASSERT: ";
    };
}
