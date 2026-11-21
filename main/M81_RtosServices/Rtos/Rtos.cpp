// @file Rtos.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#include "Rtos.hpp"

namespace M81::Rtos
{
    Rtos::Rtos(
        M90::Assert::IAssert& assert)
    :
        M80::Service(assert)
    {
        // No functionality required.
    }
}
