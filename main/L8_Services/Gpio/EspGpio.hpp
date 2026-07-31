#ifdef ESP_PLATFORM

#pragma once

#include "Gpio.hpp"


class EspGpio : public Gpio
{
public:
    EspGpio();
    ~EspGpio();

private:
    bool ConfigAsOutput(uint8_t pin) override;
    bool ConfigAsInterruptInput(uint8_t pin) override;
    bool SetLevel(uint8_t pin, bool level) override;

    bool AddInterruptHandler(int pin, void (*interruptCallbackFunction)(void*), void* arg) override;

    void DelayUs(uint32_t us) override;

    bool InstallIsrServiceWhenNotInstalledYet() override;
};

#endif // ESP_PLATFORM

