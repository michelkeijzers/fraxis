// @file Random.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "../Service.hpp"
#include "IRandom.hpp"
#include <cstdint>

namespace M90::Assert
{
    class IAssert;
}

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4250)
#endif

namespace M80::Random
{
    class Random : public Service, public IRandom
    {
    public:
        explicit Random(
            M90::Assert::IAssert& assert);

        Random(
            const Random&) = delete;

        Random& operator=(
            const Random&) = delete;

        Random(
            Random&&) = delete;
        
        Random& operator=(
            Random&&) = delete;

        virtual ~Random() override = default;

        uint8_t GetNext8() override;

        uint16_t GetNext16() override;

        uint32_t GetNext() override;

        uint32_t GetNext(
            uint32_t max) override;

        uint32_t GetNextBetween(
            uint32_t min,
            uint32_t max) override;
    };
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
