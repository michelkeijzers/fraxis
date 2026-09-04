#pragma once

#include <string>

class StringUtilities
{
public:
    static std::string Center(
        const std::string_view& text, 
        size_t width);

    static void CopyToBuffer(
        const std::string_view& text, 
        char* buffer, 
        int bufferSize);

    static int CountDifferentCharacters(
        const std::string_view& a, 
        const std::string_view& b);
};
