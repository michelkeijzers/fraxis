#ifdef ESP_PLATFORM

#include "EspGpio.hpp"
#include "../../L9_Utilities/Assert/Assert.hpp"
#include "driver/gpio.h"
#include "esp_rom_sys.h"

EspGpio::EspGpio() 
{
}

EspGpio::~EspGpio() 
{
}

bool EspGpio::ConfigAsOutput(uint8_t pin)
{
    gpio_config_t cfg = {
        .pin_bit_mask = (1ULL << pin),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    return (gpio_config(&cfg) == ESP_OK);
}

bool EspGpio::ConfigAsInterruptInput(uint8_t pin)
{
    gpio_config_t cfg = { 
        .pin_bit_mask = (1ULL << pin),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_NEGEDGE
    };
    return (gpio_config(&cfg) == ESP_OK);
}

bool EspGpio::SetLevel(uint8_t pin, bool level)
{
    return (gpio_set_level(static_cast<gpio_num_t>(pin), level) == ESP_OK);
}

bool EspGpio::InstallIsrServiceWhenNotInstalledYet()
{
    return (gpio_install_isr_service(0) == ESP_OK);
}

bool EspGpio::AddInterruptHandler(int pin, void (*interruptCallbackFunction)(void*), void* arg)
{
    return (gpio_isr_handler_add(static_cast<gpio_num_t>(pin), interruptCallbackFunction, arg) == ESP_OK);
}

void EspGpio::DelayUs(uint32_t us)
{
    esp_rom_delay_us(us);
}

#endif // ESP_PLATFORM
