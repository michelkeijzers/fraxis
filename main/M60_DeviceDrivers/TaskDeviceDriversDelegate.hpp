// @file TaskDeviceDriversDelegate.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "ITaskDeviceDriversDelegate.hpp"

namespace M60
{
    class TaskDeviceDriversDelegate : public ITaskDeviceDriversDelegate
    {
    public:
        // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
        TaskDeviceDriversDelegate(
            M90::Assert::IAssert& assert,
            M90::Log::ILog& log);

        TaskDeviceDriversDelegate(
            const TaskDeviceDriversDelegate&) = delete;
        
        TaskDeviceDriversDelegate& operator=(
            const TaskDeviceDriversDelegate&) = delete;
        
        TaskDeviceDriversDelegate(
            TaskDeviceDriversDelegate&&) = delete;
        
        TaskDeviceDriversDelegate& operator=(
            TaskDeviceDriversDelegate&&) = delete;

        // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
        virtual ~TaskDeviceDriversDelegate() override;

    protected:
        [[nodiscard]] M90::Assert::IAssert& GetAssert() const override;

        [[nodiscard]] M90::Log::ILog& GetLog() const override;

    private:
        M90::Assert::IAssert& _assert;

        M90::Log::ILog& _log;
    };
}
