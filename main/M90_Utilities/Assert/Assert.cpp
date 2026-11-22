// @file Assert.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#include "Assert.hpp"

#include "../Log/Log.hpp"
#include <string>
#include <unordered_set>
#include <utility>

namespace M90::Assert
{
    Assert::Assert(
        M90::Log::ILog& log)
    :
        _log(log)
    {
        // No functionality required.
    }

    void Assert::Fail(
        Types::ETaskId taskId,
        std::string_view message,
        std::source_location sourceLocation)
    {
#if ASSERTS_ENABLED
        _log.Text(
            taskId,
            std::string( // NOSONAR ESP32 has unreliable std::format
                sourceLocation.file_name()) + ":" +
            std::to_string(sourceLocation.line()), // NOSONAR ESP32 has unreliable std::format
            Types::ELogLevel::Critical);
        _log.Text(
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
        std::source_location sourceLocation)
    {
#if ASSERTS_ENABLED
        if (!condition)
        {
            _log.Text(
                taskId,
                std::string( // NOSONAR ESP32 has unreliable std::format
                    sourceLocation.file_name()) + ":" +
                std::to_string(sourceLocation.line()), // NOSONAR ESP32 has unreliable std::format
                Types::ELogLevel::Critical);
            _log.Text(
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
        std::source_location sourceLocation)
    {
#if ASSERTS_ENABLED
        if (condition)
        {
            _log.Text(
                taskId,
                std::string(sourceLocation.file_name()) + ":" + // NOSONAR S6185: std::string 
                                                                // instead of format
                std::to_string(sourceLocation.line()),  // NOSONAR S6185: std::string instead of 
                                                        // format
                Types::ELogLevel::Critical);

            _log.Text(
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
        std::source_location sourceLocation)
    {
#if ASSERTS_ENABLED
        IsNotNullptr(taskId, static_cast<const void*>(pointer), variableName,
            sourceLocation);
#endif // ASSERTS_ENABLED
    }

    void Assert::IsNotNullptr(
        Types::ETaskId taskId,
        const void* pointer, // NOSONAR: meant to handle any type
        std::string_view variableName,
        std::source_location sourceLocation)
    {
#if ASSERTS_ENABLED
        if (pointer == nullptr)
        {
            _log.Text(
                taskId,
                std::string(sourceLocation.file_name()) + ":" + // NOSONAR S1685 : std::string 
                                                                // instead of format
                std::to_string(sourceLocation.line()),  // NOSONAR S1685 : std::string instead of 
                                                        // format
                Types::ELogLevel::Critical);
            _log.Text(
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
        std::source_location sourceLocation)
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
            _log.Text(
                taskId,
                std::string(sourceLocation.file_name()) + ":" + // NOSONAR S6185: std::string 
                                                                // instead of format
                std::to_string(sourceLocation.line()),  // NOSONAR: std::string instead of format
                Types::ELogLevel::Critical);
            _log.Text(
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
        uint32_t value,
        uint32_t minValueIncluding,
        uint32_t maxValueExcluding,
        std::string_view message,
        std::source_location sourceLocation)
    {
#if ASSERTS_ENABLED
        IsTrue(taskId,
            (value >= minValueIncluding) && (value < maxValueExcluding),
            message, 
            sourceLocation);
#endif // ASSERTS_ENABLED
    }

    void Assert::AreUnique(
        Types::ETaskId taskId,
        std::span<uint8_t> span,
        std::string_view message,
        std::source_location sourceLocation)
    {
#if ASSERTS_ENABLED
        std::unordered_set<uint8_t> seen;
        for (uint8_t value : span)
        {
            IsTrue(taskId, !seen.contains(value), message, sourceLocation);
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
        uint32_t value)
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
        std::source_location sourceLocation)
    {
#if ASSERTS_ENABLED

        if (!std::cmp_equal(real, expected))
        {
            // NOLINTNEXTLINE(modernize-use-std-format)
            _log.Text(
                taskId,
                std::string(sourceLocation.file_name()) + // NOSONAR S6185 format
                ":" + std::to_string(sourceLocation.line()));
            _log.Text(
                taskId, std::string(ASSERT) + std::string(variableName) +
                " is expected to be " + ToString(expected) +
                " but is " + ToString(real) + "!");
            Halt();
        }
#endif // ASSERTS_ENABLED
    }

    void Assert::Equals(
        Types::ETaskId taskId,
        int real,
        int expected,
        std::string_view variableName,
        std::source_location sourceLocation)
    {
#if ASSERTS_ENABLED

        if (!std::cmp_equal(real, expected))
        {
            // NOLINTNEXTLINE(modernize-use-std-format)
            _log.Text(
                taskId,
                std::string(sourceLocation.file_name()) + // NOSONAR S6185 format
                ":" + std::to_string(sourceLocation.line()));
            _log.Text(
                taskId, std::string(ASSERT) + std::string(variableName) +
                " is expected to be " + ToString(static_cast<uint32_t>(expected)) +
                " but is " + ToString(static_cast<uint32_t>(real)) + "!");
            Halt();
        }
#endif // ASSERTS_ENABLED
    }
    void Assert::NotEquals(
        Types::ETaskId taskId,
        uint32_t real,
        uint32_t expected,
        std::string_view variableName,
        std::source_location sourceLocation)
    {
#if ASSERTS_ENABLED
        if (real == expected)
        {
            // NOLINTNEXTLINE(modernize-use-std-format)
            _log.Text(
                taskId,
                std::string(  // NOSONAR ESP32 has unreliable std::format
                    sourceLocation.file_name()) +
                ":" + // NOSONAR S6185 format
                std::to_string(sourceLocation.line()));
            _log.Text(
                taskId,
                std::string(ASSERT) + // NOSONAR ESP32 has unreliable std::format
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
        std::source_location sourceLocation)
    {
#if ASSERTS_ENABLED
        NotEquals(taskId, real, 0, variableName, sourceLocation);
#endif // ASSERTS_ENABLED
    }
}
