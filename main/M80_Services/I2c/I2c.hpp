// @file I2c.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "II2c.hpp"
#include "../Service.hpp"

namespace M90::Assert
{
    class IAssert;
}

namespace M80::I2c
{
    class I2c : public Service, public II2c
    {
    public:
        explicit I2c(
            M90::Assert::IAssert& assert);

        I2c(
            const I2c&) = delete;

        I2c& operator=(
            const I2c&) = delete;

        I2c(
            I2c&&) = delete;

        I2c& operator=(
            I2c&&) = delete;

        virtual ~I2c() = default;
    };
}
