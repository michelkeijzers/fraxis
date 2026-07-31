
#pragma once

#include <cstdint>

class Gpio
{
public:
    Gpio();
    ~Gpio();

    virtual bool ConfigAsOutput(uint8_t pin) = 0;
    virtual bool ConfigAsInterruptInput(uint8_t pin) = 0;
    virtual bool SetLevel(uint8_t pin, bool level) = 0;

    bool InstallIsrService();
    virtual bool AddInterruptHandler(int pin, void (*interruptCallbackFunction)(void*), void* arg) = 0;

    virtual void DelayUs(uint32_t us) = 0;

protected:
    virtual bool InstallIsrServiceWhenNotInstalledYet() = 0;

private:
    static bool _isIsrServiceInstalled;
};
