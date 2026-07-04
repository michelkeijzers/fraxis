#pragma once

class Debug
{
    public:
        static void PrintUInt(const char* name, unsigned int value);
        static void PrintInt(const char* name, int value);
        static void PrintChar(const char* name, char value);
        static void PrintString(const char* name, const char* value);
        static void PrintNewLine();
    
    private:
        static void OutputBuffer();

        static char _buf[256];
};
