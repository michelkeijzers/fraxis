#include "Log.hpp"
#include <cstdio>

bool Log_ENABLED = true;

#ifdef ESP_PLATFORM
    #include "esp_log.h"
#else 
    #include <windows.h>
#endif

/* static */ char Log::_buf[256];
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

void Log::Pointer(std::string_view name, const void* pointer)
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

