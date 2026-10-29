#pragma once

#include <string>

class StringUtilities
{
public:
    static std::string Center(
        std::string_view text, 
        size_t width);

    static std::string LeftAlign(
        std::string_view text,
        size_t width);

    static void CopyToBuffer(
        std::string_view source,
        char* buffer,
        size_t bufferSize);   

    static int CountDifferentCharacters(
        const std::string_view string1, 
        const std::string_view string2);
};
