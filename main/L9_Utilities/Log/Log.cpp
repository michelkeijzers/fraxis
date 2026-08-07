#include "Log.hpp"
#include <cstdio>
#ifndef ESP_PLATFORM
#include <Windows.h>
#endif

static constexpr bool Log_ENABLED = true; // NOSONAR: needs to before the incude
#ifdef ESP_PLATFORM
    #include "esp_log.h"
#endif


/* static */ char Log::_buf[256]; // NOSONAR: string is slower
/* static */ uint8_t Log::_indentation = 0;

void Log::Entry(std::string_view name)
{
    if (Log_ENABLED)
    {
        snprintf(_buf, sizeof(_buf), "%*s>%s\n", _indentation * 2, "", name.data());
        OutputBuffer();
        _indentation++;
    }
}

void Log::Exit(std::string_view name)
{
    if (Log_ENABLED)
    {
        _indentation--;
        snprintf(_buf, sizeof(_buf), "%*s<%s\n", _indentation * 2, "", name.data());
        OutputBuffer();
    }
}

void Log::Pointer(std::string_view name, const void* pointer) // NOSONAR: void* to be flexible
{
    if (Log_ENABLED)
    {
        snprintf(_buf, sizeof(_buf), "%s: %*sPointer: %p\n", name.data(), _indentation * 2, "", pointer);
        OutputBuffer();
    }
}

void Log::UInt(std::string_view name, unsigned int value)
{
    if (Log_ENABLED)
    {
        snprintf(_buf, sizeof(_buf), "%s: %ud\n", name.data(), value);
        OutputBuffer();
    }
}

void Log::Int(std::string_view name, int value)
{
    if (Log_ENABLED)
    {
        snprintf(_buf, sizeof(_buf), "%s: %d\n", name.data(), value);
        OutputBuffer();
    }
}

void Log::IntAsBits(std::string_view name, int value)
{
    if (Log_ENABLED)
    {
        // Determine bit width needed
        constexpr int BITS = sizeof(int) * 8;  // 32 bits for int

        char bits[BITS + BITS / 4 + 1] = {};   // room for spaces every 4 bits // NOSONAR: ESP32 prefers char
        int pos = 0;

        for (int i = BITS - 1; i >= 0; --i)
        {
            bits[pos++] = (value >> i) & 1 ? '1' : '0';
            // Add space after every 4 bits (except at the end)
            if (i % 4 == 0 && i != 0)
                bits[pos++] = ' ';
        }
        bits[pos] = '\0';

        snprintf(_buf, sizeof(_buf), "%s: %s\n", name.data(), bits);
        OutputBuffer();
    }
}


void Log::Char(std::string_view name, char value)
{
    if (Log_ENABLED)
    {
        snprintf(_buf, sizeof(_buf), "%s: %c\n", name.data(), value);
        OutputBuffer();
    }
}

void Log::String(std::string_view name, std::string_view value)
{
    if (Log_ENABLED)
    {
        snprintf(_buf, sizeof(_buf), "%s: %s\n", name.data(), value.data());
        OutputBuffer();
    }
}

void Log::Text(std::string_view text)
{
    if (Log_ENABLED)
    {
        snprintf(_buf, sizeof(_buf), "%s\n", text.data());
        OutputBuffer();
    }
}

void Log::OutputBuffer()
{
    if (Log_ENABLED)
    {
#ifdef ESP_PLATFORM
        ESP_LOGI("DBG", "%s", _buf);
#else
        OutputDebugStringA(_buf);
#endif
    }
}

