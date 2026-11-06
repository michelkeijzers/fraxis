#include "Gpio.hpp"

/* static */ bool Gpio::_isIsrServiceInstalled = false;

bool Gpio::InstallIsrService()
{
    if (!_isIsrServiceInstalled)
    {
        if (InstallIsrServiceWhenNotInstalledYet())
        {
            _isIsrServiceInstalled = true;
            return true;
        }
        return false;
    }
    return true;
}
