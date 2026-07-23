#pragma once

/// <summary>
/// Intellisense bypass functions/macros for the following functions:
/// - strnlen
/// </summary>

#ifdef __INTELLISENSE__

#include <stddef.h>

inline size_t strnlen(const char* s, size_t maxlen)
{
    size_t len = 0;
    while (len < maxlen && s[len] != '\0')
    {
        ++len;
    }
    return len;
}

#endif
