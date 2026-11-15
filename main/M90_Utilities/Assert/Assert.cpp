// @file Assert.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#include "Assert.hpp"

#if ASSERTS_ENABLED

#include "../Log/Log.hpp"
#include <string>

namespace M90::Assert
{
    void Assert::Fail(
        Types::ETaskId taskId,
        std::string_view message,
        std::source_location loc)
    {
#if ASSERTS_ENABLED
        M90::Log::Log::Text(
            taskId,
            std::string( // NOSONAR ESP32 has unreliable std::format
                loc.file_name()) + ":" +
            std::to_string(loc.line()), // NOSONAR ESP32 has unreliable std::format
            Types::ELogLevel::Critical);
        M90::Log::Log::Text(
            taskId,
            std::string(ASSERT) + std::string(message) + "!",
            Types::ELogLevel::Critical);
        Halt();
#endif // ASSERTS_ENABLED
    }

    void Assert::IsTrue(
        Types::ETaskId taskId,
        bool condition,
        std::string_view message,
        std::source_location loc)
    {
#if ASSERTS_ENABLED
        if (!condition)
        {
            M90::Log::Log::Text(
                taskId,
                std::string( // NOSONAR ESP32 has unreliable std::format
                    loc.file_name()) + ":" +
                std::to_string(loc.line()), // NOSONAR ESP32 has unreliable std::format
                Types::ELogLevel::Critical);
            M90::Log::Log::Text(
                taskId,
                std::string(ASSERT) + std::string(message) + "!",
                Types::ELogLevel::Critical);
            Halt();
        }
#endif // ASSERTS_ENABLED
    }

    void Assert::IsFalse(
        Types::ETaskId taskId,
        bool condition,
        std::string_view message,
        std::source_location loc)
    {
#if ASSERTS_ENABLED
        if (condition)
        {
            M90::Log::Log::Text(
                taskId,
                std::string(loc.file_name()) + ":" + // NOSONAR S6185: std::string instead of format
                std::to_string(loc.line()), // NOSONAR S6185: std::string instead of format
                Types::ELogLevel::Critical);

            M90::Log::Log::Text(
                taskId,
                std::string(ASSERT) + std::string(message) + "!",
                Types::ELogLevel::Critical);
            Halt();
        }
#endif // ASSERTS_ENABLED
    }

    void Assert::IsNotNullptr(
        Types::ETaskId taskId,
        void* pointer, // NOSONAR: meant to handle any type
        std::string_view variableName,
        std::source_location loc)
    {
#if ASSERTS_ENABLED
        IsNotNullptr(taskId, static_cast<const void *>(pointer), variableName,
                     loc);
#endif // ASSERTS_ENABLED
    }

    void Assert::IsNotNullptr(
        Types::ETaskId taskId,
        const void* pointer, // NOSONAR: meant to handle any type
        std::string_view variableName,
        std::source_location loc)
    {
#if ASSERTS_ENABLED
        if (pointer == nullptr)
        {
            M90::Log::Log::Text(
                taskId,
                std::string(loc.file_name()) + ":" + // NOSONAR S1685 : std::string instead of format
                std::to_string(loc.line()), // NOSONAR S1685 : std::string instead of format
                Types::ELogLevel::Critical);
            M90::Log::Log::Text(
                taskId,
                std::string(ASSERT) + std::string(variableName) + " is nullptr!",
                Types::ELogLevel::Critical);
            Halt();
        }
#endif // ASSERTS_ENABLED
    }

    void Assert::IsEsp32Pin(
        Types::ETaskId taskId,
        uint8_t pin,
        std::string_view message,
        std::source_location loc)
    {
#if ASSERTS_ENABLED
        bool isPinValid =
            (
            (pin >= 1 && pin <= 2) || // OK for general IO, ADC, RTC
            (pin == 3) || // Strapping pin, boot JTAG source, avoid strong pulls at reset
            (pin >= 4 && pin <= 8) || // OK for general IO, ADC, touch, RTC
            // 9-13 often used for SPI flash
            // 14 often used for SPI flash/PSRAM
            (pin >= 15 && pin <= 18) || // OK for general IO, ADC, RTC
            // 19-20 used for USB/JTAG
            // 21 used for OTG 
            // 22-25 do not exist
            // 26-32 used for internal flash 
            // 33 - 37: often used for spi flash/PSRAM 
            (pin >= 38 && pin <= 42) || // OK for general IO (38: check board if tied to flash 
            // 43-44 Used for USB-UART
            (pin >= 45 && pin <= 46) || // OK but strapping pin, avoid strong pulls
            (pin >= 47) || // OFten ree, good for LEDs/buttons
            (pin == 48)); // Drives on board RRG bLED on DevKit C-1

        if (!isPinValid)
        {
            M90::Log::Log::Text(
                taskId,
                std::string(loc.file_name()) + ":" + // NOSONAR S6185: std::string instead of format
                std::to_string(loc.line()),  // NOSONAR: std::string instead of format
                Types::ELogLevel::Critical);
            M90::Log::Log::Text(
                taskId,
                std::string(ASSERT) + "Do not use pin" + // NOSONAR : std::string instead of format
                std::to_string(pin) // NOSONAR ESP32 has unreliable std::format
                + "on ESP32 S3! " +
                std::string(message), Types::ELogLevel::Critical);
            Halt();
        }
#endif // ASSERTS_ENABLED
    }
    
    void Assert::IsBetween(
        Types::ETaskId taskId, 
        const uint32_t value,
        const uint32_t minValueIncluding,
        const uint32_t maxValueExcluding,
        std::string_view message = "")
    {
#if ASSERTS_ENABLED
        IsTrue(taskId,
               (value >= minValueIncluding) && (value < maxValueExcluding),
               message);
#endif // ASSERTS_ENABLED
    }

    void Assert::AreUnique(
        Types::ETaskId taskId, 
        std::span<const uint8_t> span,
        std::string_view message = "")
    {
#if ASSERTS_ENABLED
        std::unordered_set<uint8_t> seen;
        for (const uint8_t &value : span)
        {
            IsTrue(taskId, !seen.contains(value), message);
            seen.insert(value);
        }
#endif // ASSERTS_ENABLED
    }

    void Assert::Halt()
    {
#if ASSERTS_ENABLED
        abort();
        while (true);
        // Wait forever.
#endif // ASSERTS_ENABLED
    }

    std::string Assert::ToString(
        const uint32_t value)
    {
#if ASSERTS_ENABLED
        return std::to_string(value);
#else
        return "";
#endif // ASSERTS_ENABLED
    }

    void Assert::Equals(
        Types::ETaskId taskId, 
        uint32_t real, 
        uint32_t expected,
        std::string_view variableName,
        std::source_location loc = std::source_location::current())
    {
#if ASSERTS_ENABLED

        if (!std::cmp_equal(real, expected))
        {
            // NOLINTNEXTLINE(modernize-use-std-format)
            M90::Log::Log::Text(
                taskId,
                std::string(loc.file_name()) + // NOSONAR S6185 format
                    ":" + std::to_string(loc.line()));
            M90::Log::Log::Text(
                taskId, std::string(ASSERT) + std::string(variableName) +
                            " is expected to be " + ToString(expected) +
                            " but is " + ToString(real) + "!");
            Halt();
        }
#endif // ASSERTS_ENABLED
    }

    void Assert::NotEquals(
        Types::ETaskId taskId, 
        uint32_t &real, 
        uint32_t &expected,
        std::string_view variableName,
        std::source_location loc = std::source_location::current())
    {
#if ASSERTS_ENABLED
        if (real == expected)
        {
            // NOLINTNEXTLINE(modernize-use-std-format)
            M90::Log::Log::Text(
                taskId,
                std::string(loc.file_name()) +
                    ":" + // NOSONAR S6185 format
                    std::to_string(loc.line()));
            M90::Log::Log::Text(
                taskId, 
                std::string(ASSERT) +
                    std::string(variableName) +
                    " is not expected to be " +
                    std::to_string(expected) + "!");
            Halt();
        }
#endif // ASSERTS_ENABLED
    }

    void Assert::IsNot0(
        Types::ETaskId taskId,
        uint32_t real,
        std::string_view variableName,
        std::source_location loc = std::source_location::current())
    {
#if ASSERTS_ENABLED
        NotEquals(taskId, real, 0, variableName, loc);
#endif // ASSERTS_ENABLED     }
    }
