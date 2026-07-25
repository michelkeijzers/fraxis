#include "StringUtils.hpp"
#include "../../L9_Utils/Assert/Assert.hpp"

/* static */ std::string StringUtils::Center(const std::string& text, size_t width)
{
    if (text.size() >= width)
        return text.substr(0, width);

    size_t total = width - text.size();
    size_t left = total / 2;
    size_t right = total - left;

    return std::string(left, ' ') + text + std::string(right, ' ');
}

/* static */ void StringUtils::CopyToBuffer(const std::string& text, char* buffer, int bufferSize)
{
    Assert::IsTrue(text.size() <= bufferSize, "String too long for buffer");
    for (int i = 0; i < text.size(); i++)
    {
        buffer[i] = text[i];
    }
    if (text.size() < bufferSize)
    {
        buffer[text.size()] = '\0';
    }
}