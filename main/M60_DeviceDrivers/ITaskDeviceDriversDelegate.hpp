// @file ITaskDeviceDriversDelegate.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

namespace M90
{
    namespace Assert
    {
        class IAssert;
    }

    namespace Log
    {
        class ILog;
    }
}

namespace M60
{
    class ITaskDeviceDriversDelegate
    {
    public:
        virtual ~ITaskDeviceDriversDelegate() = default;

        [[nodiscard]] virtual M90::Assert::IAssert& GetAssert() const = 0;

        [[nodiscard]] virtual M90::Log::ILog& GetLog() const = 0;
    };
}
