// @file I2s.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "II2s.hpp" 
#include "../Service.hpp"

namespace M90::Assert
{
    class IAssert;
}

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4250)
#endif

namespace M80::I2s
{
    class I2s : public Service, public II2s
    {
    public:
        explicit I2s(
            M90::Assert::IAssert& assert);

        I2s(
            const I2s&) = delete;

        I2s& operator=(
            const I2s&) = delete;

        I2s(
            I2s&&) = delete;

        I2s& operator=(
            I2s&&) = delete;

        virtual ~I2s() = default;
    };
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
