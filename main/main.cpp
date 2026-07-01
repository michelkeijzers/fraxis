#include "driver/i2c.h"
#include "driver/gpio.h"
#include "Core/Services/Rtos.hpp"
#include "ESP32/Services/EspRtos.hpp"
#include "ESP32/Components/EspLcd1602Display.hpp"
#include "Core/Menu/MenuSimulator.hpp"
#include "ESP32/EspI2c.hpp"
#include "Core/Components/PinIo.hpp"
#include "ESP32/Components/EspMcp23017.hpp"

extern "C" void app_main(void)
{
    printf("Starting Menu Simulator...\n");
    static EspRtos espRtos;
    Rtos::Set(&espRtos);
    EspI2c espI2c(I2C_NUM_0, GPIO_NUM_16, GPIO_NUM_17, 100000);
    espI2c.Init();
    EspLcd1602Display espLcdDisplay(espI2c);
    EspMcp23017 espMcp23017(espI2c);
    PinIo pinIo(espMcp23017);
    MenuSimulator simulator(espLcdDisplay, pinIo);
    simulator.run();
}
