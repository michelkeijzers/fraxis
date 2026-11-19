// @file RtosTask.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "../../M80_Services/Service.hpp"
#include "IRtosTask.hpp"
#include <cstdint>

namespace M90::Assert
{
    class IAssert;
}

namespace M81::RtosTask
{
    class RtosTask : public M80::Service, public IRtosTask
    {
    public:
        // NOLINTNEXTLINE(modernize-use-using)
        typedef void (*TaskFunction_t)(void*);

        explicit RtosTask(
            M90::Assert::IAssert& assert);

        RtosTask(
            const RtosTask&) = delete;

        RtosTask& operator=(
            const RtosTask&) = delete;

        RtosTask(
            RtosTask&&) = delete;

        RtosTask& operator=(
            RtosTask&&) = delete;

        virtual ~RtosTask() = default;
    };
}
