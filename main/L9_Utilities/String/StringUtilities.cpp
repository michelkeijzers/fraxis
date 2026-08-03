#include "StringUtilities.hpp"
#include "../Assert/Assert.hpp"
#include "../Array/ArrayUtilities.hpp"

/* static */ std::string StringUtilities::Center(
    const std::string_view& text, 
    size_t width)
{
    if (text.size() >= width)
    {
        return std::string(text.substr(0, width));
    }

    size_t total = width - text.size();
    size_t left = total / 2;
    size_t right = total - left;

    return std::string(left, ' ') + std::string(text) + std::string(right, ' ');
}

/* static */ void StringUtilities::CopyToBuffer(
    const std::string_view& text,
    char* buffer,
    int bufferSize)
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

/* static */ int StringUtilities::CountDifferentCharacters(
    const std::string_view& a,
    const std::string_view& b)
{
    const size_t len = std::min(a.size(), b.size());
    return ArrayUtilities::CountDifferent(a.data(), b.data(), static_cast<int>(len));
}
