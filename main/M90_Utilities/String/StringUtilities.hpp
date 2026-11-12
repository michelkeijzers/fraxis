// @file StringUtilities.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <string>

namespace M90::String
{
    class StringUtilities
    {
    public:
        static std::string Center(
            std::string_view text,
            size_t width);

        static std::string LeftAlign(
            std::string_view text,
            size_t width);

        static void CopyToBuffer(
            std::string_view source,
            char* buffer,
            size_t bufferSize);

        static int CountDifferentCharacters(
            const std::string_view string1,
            const std::string_view string2);
    };
}
