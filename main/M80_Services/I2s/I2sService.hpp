// @file I2sService.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "II2sService.hpp" 
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
    class I2sService : public Service, public II2sService
    {
    public:
        explicit I2sService(
            M90::Assert::IAssert& assert);

        I2sService(
            const I2sService&) = delete;

        I2sService& operator=(
            const I2sService&) = delete;

        I2sService(
            I2sService&&) = delete;

        I2sService& operator=(
            I2sService&&) = delete;

        virtual ~I2sService() = default;
    };
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
