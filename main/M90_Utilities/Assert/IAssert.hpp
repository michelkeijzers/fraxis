// @file Assert.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "../Log/Log.hpp"
#include "../../M30_Messages/Types.hpp"
#include <string>
#include <list>
#include <cassert>
#include <unordered_set>
#include <source_location>
#include <cstdlib>
#include <utility>
#include <span>

namespace M90::Log
{
    class ILog;
}

namespace M90::Assert
{
    class IAssert
    {
    public:
        virtual ~IAssert() = default;

        [[noreturn]] virtual void Fail(
            Types::ETaskId taskId,
            std::string_view message = "",
            std::source_location sourceLocation = std::source_location::current()) = 0;

        virtual void IsTrue(
            Types::ETaskId taskId,
            bool condition,
            std::string_view message = "",
            std::source_location sourceLocation = std::source_location::current()) = 0;

        virtual void IsFalse(
            Types::ETaskId taskId,
            bool condition,
            std::string_view message = "",
            std::source_location sourceLocation = std::source_location::current()) = 0;

        virtual void IsNotNullptr(
            Types::ETaskId taskId,
            void* pointer,
            std::string_view variableName = "",
            std::source_location sourceLocation = std::source_location::current()) = 0;

        virtual void IsNotNullptr(
            Types::ETaskId taskId,
            const void* pointer,
            std::string_view variableName = "",
            std::source_location sourceLocation = std::source_location::current()) = 0;

        virtual void IsEsp32Pin(
            Types::ETaskId taskId,
            uint8_t pin,
            std::string_view message = "",
            std::source_location sourceLocation = std::source_location::current()) = 0;

        virtual std::string ToString(
            uint32_t value) = 0;
        
        virtual void Equals(
            Types::ETaskId taskId,
            uint32_t real,
            uint32_t expected,
            std::string_view variableName,
            std::source_location sourceLocation = std::source_location::current()) = 0;
       
        virtual void Equals(
            Types::ETaskId taskId,
            int real,
            int expected,
            std::string_view variableName,
            std::source_location sourceLocation = std::source_location::current()) = 0;

        virtual void NotEquals(
            Types::ETaskId taskId,
            uint32_t real,
            uint32_t expected,
            std::string_view variableName,
            std::source_location sourceLocation = std::source_location::current()) = 0;
       
        virtual void IsNot0(
            Types::ETaskId taskId,
            uint32_t real,
            std::string_view variableName,
            std::source_location sourceLocation = std::source_location::current()) = 0;
        
        virtual void IsBetween(
            Types::ETaskId taskId,
            uint32_t value,
            uint32_t minValueIncluding,
            uint32_t maxValueExcluding,
            std::string_view message = "",
            std::source_location sourceLocation = std::source_location::current()) = 0;
        
        virtual void AreUnique(
            Types::ETaskId taskId,
            std::span<uint8_t> span,
            std::string_view message = "",
            std::source_location sourceLocation = std::source_location::current()) = 0;
    };
}
