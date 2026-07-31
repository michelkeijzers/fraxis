#include "WindowsGpio.hpp"

WindowsGpio::WindowsGpio()
{
}

WindowsGpio::~WindowsGpio()
{
}

bool WindowsGpio::ConfigAsOutput(uint8_t pin)
{
    return true;
}

bool WindowsGpio::ConfigAsInterruptInput(uint8_t pin)
{
    return true;
}

bool WindowsGpio::SetLevel(uint8_t pin, bool level)
{
    return true;
}


bool WindowsGpio::InstallIsrServiceWhenNotInstalledYet()
{
    return true;
}

bool WindowsGpio::AddInterruptHandler(int pin, void (*interruptCallbackFunction)(void*), void* arg)
{
    return true;
}

void WindowsGpio::DelayUs(uint32_t us)
{
    // Ignore us delay.
}