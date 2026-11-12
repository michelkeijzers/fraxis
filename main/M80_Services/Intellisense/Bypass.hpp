// @file Bypass.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

/// <summary>
/// Intellisense bypass functions/macros for the following functions:
/// - strnlen
/// </summary>

#ifdef __INTELLISENSE__

#include <stddef.h>

namespace M80::Intellisense
{
    inline size_t strnlen(
        const char* s,
        size_t maxlen)
    {
        size_t len = 0;
        while (len < maxlen && s[len] != '\0')
        {
            ++len;
        }
        return len;
    }
}

#endif
