#pragma once

#include "Gpio.hpp"

class WindowsGpio : public Gpio
{
public:
    WindowsGpio();
    ~WindowsGpio();

    bool ConfigAsOutput(uint8_t pin) override;
    bool ConfigAsInterruptInput(uint8_t pin) override;
    bool SetLevel(uint8_t pin, bool level) override;

    bool AddInterruptHandler(int pin, void (*interruptCallbackFunction)(void*), void* arg) override;

    void DelayUs(uint32_t us) override;

private:
    bool InstallIsrServiceWhenNotInstalledYet() override;
};
