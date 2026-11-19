// @file Rtos.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "../../M80_Services/Service.hpp"
#include "IRtos.hpp"
#include <cstdint>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4250)
#endif

namespace M81
{
    namespace RtosQueue
    {
        class IRtosQueue;
    }

    namespace RtosTask
    {
        class IRtosTask;
    }
}

namespace M90::Assert
{
    class IAssert;
}

namespace M81::Rtos
{
    class Rtos : public M80::Service, public IRtos
    {
    public:
        using TaskFunction_t = void (*)(void*);

        explicit Rtos(
            M90::Assert::IAssert& assert);

        Rtos(
            const Rtos&) = delete;

        Rtos& operator=(
            const Rtos&) = delete;

        Rtos(
            Rtos&&) = delete;
        
        Rtos& operator=(
            Rtos&&) = delete;

        virtual ~Rtos() = default;
    };
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
