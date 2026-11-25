// @file TaskDeviceDriversDelegate.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only
 
#include "TaskDeviceDriversDelegate.hpp"
#include "../M90_Utilities/Assert/IAssert.hpp"

namespace M60
{
    TaskDeviceDriversDelegate::TaskDeviceDriversDelegate(
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log)
    : 
        _assert(assert),
        _log(log)
    {
        // No actions required.
    }

    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    TaskDeviceDriversDelegate::~TaskDeviceDriversDelegate() = default;

    M90::Assert::IAssert& TaskDeviceDriversDelegate::GetAssert() const
    {
        return _assert;
    }

    M90::Log::ILog& TaskDeviceDriversDelegate::GetLog() const
    {
        return _log;
    }
}
