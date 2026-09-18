#include "Gpio.hpp"

/* static */ bool Gpio::_isIsrServiceInstalled = false;

Gpio::Gpio()
{
}

Gpio::~Gpio()
{
}

bool Gpio::InstallIsrService()
{
    if (!_isIsrServiceInstalled)
    {
        return InstallIsrServiceWhenNotInstalledYet();
    }
    return true;
}