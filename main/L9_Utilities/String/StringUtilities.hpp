#pragma once

#include <string>

class StringUtilities
{
public:
    static std::string Center(const std::string& text, size_t width);
    static void CopyToBuffer(const std::string& text, char* buffer, int bufferSize);
    static int CountDifferentCharacters(const std::string& a, const std::string& b);
};
