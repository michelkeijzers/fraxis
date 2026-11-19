// @file StringUtilities.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "IStringUtilities.hpp"

namespace M90::String
{
    class StringUtilities : IStringUtilities
    {
    public:
        StringUtilities(
            M90::Assert::IAssert &assert);

        std::string Center(
            std::string_view text,
            size_t width) override;

        std::string LeftAlign(
            std::string_view text,
            size_t width) override;

        void CopyToBuffer(
            std::string_view source,
            char* buffer,
            size_t bufferSize) override ;

        int CountDifferentCharacters(
            const std::string_view string1,
            const std::string_view string2) override;

        M90::Assert::IAssert& GetAssert() override;

    private:
        M90::Assert::IAssert &_assert;
    };
}
