#include "Assert.hpp"
#include "../Debug/debug.hpp"

void Assert::IsNotNullptr(bool condition, const char* message /* = nullptr */) 
{
    if (!condition)
    {
        if (message == nullptr)
        {
            message = "ASSERT: Assertion failed!";
        }
        Debug::PrintText(message);
        while (true);
    }
};
