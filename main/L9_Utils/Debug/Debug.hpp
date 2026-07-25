#pragma once

#include <string>

class Debug
{
    public:
        static void PrintUInt(std::string name, unsigned int value);
        static void PrintInt(std::string name, int value);
        static void PrintChar(std::string name, char value);
        static void PrintString(std::string name, std::string value);
        static void PrintText(std::string text);
        static void PrintNewLine();
    
    private:
        static void OutputBuffer();

        static char _buf[256];
};
