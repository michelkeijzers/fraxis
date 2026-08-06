#pragma once

#include <string>

class Log
{
public:
    static void Entry(std::string_view name);
    static void Exit(std::string_view name);
    static void Pointer(std::string_view name, const void* pointer);
    static void UInt(std::string_view name, unsigned int value);
    static void Int(std::string_view name, int value);
    static void IntAsBits(std::string_view name, int value);
    static void Char(std::string_view name, char value);
    static void String(std::string_view name, std::string_view value);
    static void Text(std::string_view text);
    
private:
    static void OutputBuffer();

    static char _buf[256];
    static uint8_t _indentation;
};
