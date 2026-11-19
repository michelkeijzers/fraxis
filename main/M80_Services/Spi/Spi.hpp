// @file Spi.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "../Service.hpp"
#include "ISpi.hpp"

namespace M90::Assert
{
    class IAssert;
}

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4250)
#endif

namespace M80::Spi
{
    class Spi : public Service, public ISpi
    {
    public:
        explicit Spi(
            M90::Assert::IAssert& assert);

        Spi(
            const Spi&) = delete;

        Spi& operator=(
            const Spi&) = delete;

        Spi(
            Spi&&) = delete;

        Spi& operator=(
            Spi&&) = delete;

        virtual ~Spi() = default;
    };
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
