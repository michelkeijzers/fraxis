#include "driver/i2c.h"
#include "driver/gpio.h"
#include "ESP32/Components/EspLcd1602Display.hpp"
#include "Core/Menu/MenuSimulator.hpp"
#include "ESP32/EspI2c.hpp"

extern "C" void app_main(void)
{
    printf("Starting Menu Simulator...\n");
    EspI2c espI2c(I2C_NUM_0, GPIO_NUM_16, GPIO_NUM_17, 100000);
    espI2c.Init();
    EspLcd1602Display espLcdDisplay(espI2c);
    MenuSimulator simulator(espLcdDisplay);
    simulator.run();
}
