// @file IRtosTask.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <cstdint>

namespace M81::RtosTask
{
    class IRtosTask
    {
    public:
        // NOLINTNEXTLINE(modernize-use-using)
        typedef void (*TaskFunction_t)(void*);

        IRtosTask() = default;

        IRtosTask(
            const IRtosTask&) = delete;

        IRtosTask& operator=(
            const IRtosTask&) = delete;

        IRtosTask(
            IRtosTask&&) = delete;

        IRtosTask& operator=(
            IRtosTask&&) = delete;

        virtual ~IRtosTask() = default;

        virtual void Start() = 0;

        virtual bool DelayTask(
            uint32_t microSeconds) = 0;

        virtual uint32_t GetTaskTickCount() = 0;
    };
}
