#pragma once

#include <string>

class Debug
{
    public:
        static void PrintUInt(std::string_view name, unsigned int value);
        static void PrintInt(std::string_view name, int value);
        static void PrintChar(std::string_view name, char value);
        static void PrintString(std::string_view name, std::string_view value);
        static void PrintText(std::string_view text);
        static void PrintNewLine();
    
    private:
        static void OutputBuffer();

        static char _buf[256];
};
