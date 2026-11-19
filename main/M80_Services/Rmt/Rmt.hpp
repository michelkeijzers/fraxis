// @file Rmt.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "../Service.hpp"
#include "IRmt.hpp" 

namespace M90::Assert
{
    class IAssert;
}

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4250)
#endif

namespace M80::Rmt
{
    class Rmt : public Service, public IRmt
    {
    public:
        explicit Rmt(
            M90::Assert::IAssert& assert);

        Rmt(
            const Rmt&) = delete;

        Rmt& operator=(
            const Rmt&) = delete;

        Rmt(
            Rmt&&) = delete;

        Rmt& operator=(
            Rmt&&) = delete;

        virtual ~Rmt() = default;
    };
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
