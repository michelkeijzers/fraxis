#include "Assert.hpp"
#include "../Debug/debug.hpp"
#include <string>

static std::string ASSERT = std::string("ASSERT: ");

/* static */ void Assert::IsTrue(bool condition, std::string message)
{
    if (condition)
    {
        Debug::PrintText(ASSERT + message + "!");
        while (true);
    }
}

/* static */ void Assert::IsFalse(bool condition, std::string message)
{
    if (condition)
    {
        Debug::PrintText(ASSERT + message + "!");
        while (true);
    }
}

/* static */ void Assert::IsNotNullptr(bool condition, std::string variableName)
{
    if (!condition)
    {
        Debug::PrintText(ASSERT + variableName + " is null!");
        while (true);
    }
}

/* static*/ void Assert::Equals(int real, int expected, std::string variableName)
{
    if (real != expected)
    {
        Debug::PrintText(ASSERT + variableName + " is expected to be " + std::to_string(expected) + " but is " + 
        std::to_string(real) + "!");
        while (true);
    }
}
