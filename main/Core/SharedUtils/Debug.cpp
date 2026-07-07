#include "Debug.hpp"
#include <cstdio>

bool DEBUG_ENABLED = true;

#ifdef _WIN32
    #include <windows.h>
#else 
    #include "esp_log.h"
#endif

/* static */ char Debug::_buf[256];

void Debug::PrintUInt(const char* name, unsigned int value)
{
    if (DEBUG_ENABLED)
    {
        snprintf(_buf, sizeof(_buf), "%s: %ud | ", name, value);
        OutputBuffer();
    }
}

void Debug::PrintInt(const char* name, int value)
{
    if (DEBUG_ENABLED)
    {
        snprintf(_buf, sizeof(_buf), "%s: %d | ", name, value);
        OutputBuffer();
    }
}

void Debug::PrintChar(const char* name, char value)
{
    if (DEBUG_ENABLED)
    {
        snprintf(_buf, sizeof(_buf), "%s: %c | ", name, value);
        OutputBuffer();
    }
}

void Debug::PrintString(const char* name, const char* value)
{
    if (DEBUG_ENABLED)
    {
        snprintf(_buf, sizeof(_buf), "%s: %s | ", name, value);
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

void Debug::PrintText(const char* text)
{
    if (DEBUG_ENABLED)
    {
        snprintf(_buf, sizeof(_buf), text);
        OutputBuffer();
        snprintf(_buf, sizeof(_buf), " | ");
        OutputBuffer();
    }
}

void Debug::OutputBuffer()
{
    if (DEBUG_ENABLED)
    {
#ifdef _WIN32
        OutputDebugStringA(_buf);
#else
        ESP_LOGI("DBG", "%s", _buf);
#endif
    }
}

