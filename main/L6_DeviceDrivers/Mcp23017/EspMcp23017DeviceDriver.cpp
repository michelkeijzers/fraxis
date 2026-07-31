#ifdef ESP_PLATFORM

#include "EspMcp23017DeviceDriver.hpp"
#include "../../L5_DeviceModels/Mcp23017/Mcp23017DeviceModel.hpp"
#include "../../L9_Utilities/Assert/Assert.hpp"
#include "esp_attr.h"
#include "driver/gpio.h"

EspMcp23017DeviceDriver::EspMcp23017DeviceDriver()
{
}

EspMcp23017DeviceDriver::~EspMcp23017DeviceDriver()
{
}

static void IRAM_ATTR InterruptHandler(void* arg)
{
    Mcp23017DeviceDriver::SetInterruptTriggered();
}

void EspMcp23017DeviceDriver::InitializeInterruptOnEsp(uint8_t interruptPin)
{
    gpio_config_t io_conf = {};
    io_conf.intr_type = GPIO_INTR_NEGEDGE;        // MCP INT is active LOW
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = (1ULL << interruptPin);
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;      // MCP INT is open-drain

    Assert::Equals(gpio_config(&io_conf), ESP_OK, "Failed to configure GPIO");
    Assert::Equals(gpio_install_isr_service(0), ESP_OK, "Failed to install GPIO ISR service");
    Assert::Equals(gpio_isr_handler_add(static_cast<gpio_num_t>(interruptPin), InterruptHandler, nullptr), ESP_OK, 
        "Failed to add GPIO ISR handler");
}

#endif // ESP_PLATFORM
