#include "Debug.hpp"
#include <cstdio>

bool DEBUG_ENABLED = true;

#ifdef ESP_PLATFORM
    #include "esp_log.h"
#else 
    #include <windows.h>
#endif

/* static */ char Debug::_buf[256];


void Debug::PrintUInt(std::string_view name, unsigned int value)
{
    if (DEBUG_ENABLED)
    {
        snprintf(_buf, sizeof(_buf), "%s: %ud | ", name.data(), value);
        OutputBuffer();
    }
}

void Debug::PrintInt(std::string_view name, int value)
{
    if (DEBUG_ENABLED)
    {
        snprintf(_buf, sizeof(_buf), "%s: %d | ", name.data(), value);
        OutputBuffer();
    }
}

void Debug::PrintChar(std::string_view name, char value)
{
    if (DEBUG_ENABLED)
    {
        snprintf(_buf, sizeof(_buf), "%s: %c | ", name.data(), value);
        OutputBuffer();
    }
}

void Debug::PrintString(std::string_view name, std::string_view value)
{
    if (DEBUG_ENABLED)
    {
        snprintf(_buf, sizeof(_buf), "%s: %s | ", name.data(), value.data());
        OutputBuffer();
    }
}

void Debug::PrintNewLine()
{
    if (DEBUG_ENABLED)
    {
        snprintf(_buf, sizeof(_buf), "\n");
        OutputBuffer();
    }
}

void Debug::PrintText(std::string_view text)
{
    if (DEBUG_ENABLED)
    {
        snprintf(_buf, sizeof(_buf), "%s", text.data());
        OutputBuffer();

        snprintf(_buf, sizeof(_buf), " | ");
        OutputBuffer();
    }
}

void Debug::OutputBuffer()
{
    if (DEBUG_ENABLED)
    {
#ifdef ESP_PLATFORM
        ESP_LOGI("DBG", "%s", _buf);
#else
        OutputDebugStringA(_buf);
#endif
    }
}

