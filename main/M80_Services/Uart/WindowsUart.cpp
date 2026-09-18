#include "WindowsUart.hpp"
#include "../../M90_Utilities/Assert/Assert.hpp"
#include <cstring>

void WindowsUart::Initialize(
    uint32_t baudRate,
    uint16_t rxBufferSize,
    uint16_t txBufferSize)
{
    // No initialization needed.
}

void WindowsUart::Send(
    const char* data,
    const uint16_t length)
{
    Assert::IsNotNullptr(Types::ETaskId::DiagnosticsTask, (void*)data, "data");
    //TODO
}
