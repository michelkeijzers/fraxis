// @file StringUtilities.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <string>

namespace M90::Assert
{
    class IAssert;
}

namespace M90::String
{
    class IStringUtilities
    {
    public:
        IStringUtilities() = default;

        virtual std::string Center(
            std::string_view text,
            size_t width) = 0;

        virtual std::string LeftAlign(
            std::string_view text,
            size_t width) = 0;

        virtual void CopyToBuffer(
            std::string_view source,
            char* buffer,
            size_t bufferSize) = 0;

        virtual int CountDifferentCharacters(
            const std::string_view string1,
            const std::string_view string2) = 0;

        virtual M90::Assert::IAssert& GetAssert() = 0;
    };
}
