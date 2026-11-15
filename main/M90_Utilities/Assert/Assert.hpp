// @file Assert.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#define ASSERTS_ENABLED 1

#include "IAssert.hpp" 
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
    class Assert : public IAssert
    {
    public:
        [[noreturn]] void Fail(
            Types::ETaskId taskId,
            std::string_view message = "",
            std::source_location loc = std::source_location::current()) override;

        void IsTrue(
            Types::ETaskId taskId,
            bool condition,
            std::string_view message = "",
            std::source_location loc = std::source_location::current()) override;

        void IsFalse(
            Types::ETaskId taskId,
            bool condition,
            std::string_view message = "",
            std::source_location loc = std::source_location::current()) override;

        void IsNotNullptr(
            Types::ETaskId taskId,
            void* pointer,
            std::string_view variableName = "",
            std::source_location loc = std::source_location::current()) override;

        void IsNotNullptr(
            Types::ETaskId taskId,
            const void* pointer,
            std::string_view variableName = "",
            std::source_location loc = std::source_location::current()) override;

        void IsEsp32Pin(
            Types::ETaskId taskId,
            uint8_t pin,
            std::string_view message = "",
            std::source_location loc = std::source_location::current()) override;

        std::string ToString(
            const uint32_t value) override;

        void Equals(
            Types::ETaskId taskId,
            uint32_t real,
            uint32_t expected,
            std::string_view variableName,
            std::source_location loc = std::source_location::current()) override;
        
        void NotEquals(
            Types::ETaskId taskId,
            uint32_t real,
            uint32_t expected,
            std::string_view variableName,
            std::source_location loc = std::source_location::current()) override;

        void IsBetween(
            Types::ETaskId taskId,
            uint32_t value,
            uint32_t minValueIncluding,
            uint32_t maxValueExcluding,
            std::string_view message = "");

        void AreUnique(
            Types::ETaskId taskId,
            std::span<uint8_t> span,
            std::string_view message = "");

        [[noreturn]] static void Halt();

    private:
        static constexpr std::string_view ASSERT = "ASSERT: ";
    };
}
