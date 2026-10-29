#include "StringUtilities.hpp"
#include "../Assert/Assert.hpp"
#include "../Container/ContainerUtilities.hpp"

/* static */ std::string StringUtilities::Center(
    std::string_view text, 
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

/* static */ std::string StringUtilities::LeftAlign(
    std::string_view text,
    size_t width)
{
    if (text.size() >= width)
    {
        return std::string{ text.substr(0, width) };
    }

    std::string result;
    result.reserve(width);

    result.append(text);
    result.append(width - text.size(), ' ');

    return result;
}

/* static */ void StringUtilities::CopyToBuffer(
    std::string_view source,
    char* buffer,
    size_t bufferSize)
{
    Assert::IsTrue(
        Types::ETaskId::System, 
        source.size() <= bufferSize, 
        "String too long for buffer");

    for (size_t index = 0; index < source.size(); index++)
    {
        buffer[index] = source[index];
    }
    if (source.size() < bufferSize)
    {
        buffer[source.size()] = '\0';
    }
}

/* static */ int StringUtilities::CountDifferentCharacters(
    const std::string_view stringA,
    const std::string_view stringB)
{
    // NOSONAR: TODO The System task is not fully true, maybe add an unknown taskId).
    Assert::Equals(
        Types::ETaskId::System, stringA.size(), stringB.size(), "string size");
    int count = 0;
    for (size_t index = 0; index < stringA.size(); index++)
    {
        if (!(stringA[index] == stringB[index]))
        {
            count++;
        }
    }
    return count;
}
