#include "driver/i2c.h"
#include "driver/gpio.h"
#include "ESP32/Services/EspRtos.hpp"
#include "ESP32/Services/EspRtosQueue.hpp"
#include "ESP32/Services/EspTimer.hpp"
#include "ESP32/Components/EspLcd1602Display.hpp"
#include "ESP32/Components/EspMcp23017.hpp"
#include "ESP32/Components/EspTm1637.hpp"
#include "Core/Menu/MenuSimulator.hpp"
#include "ESP32/EspI2c.hpp"
#include "Core/Components/PinIo.hpp"

extern "C" void app_main(void)
{
    printf("Starting Menu Simulator...\n");

    EspRtos espRtos;
    EspRtosQueue espRtosQueue(10, sizeof(int)); // TODO

    // I2C
    EspI2c espI2c(I2C_NUM_0, GPIO_NUM_16, GPIO_NUM_17, 100000);
    espI2c.Init();
    EspLcd1602Display espLcdDisplay(espI2c);
    EspMcp23017 espMcp23017(espI2c);
    PinIo pinIo(espMcp23017);
    
    // TM1637
    EspTm1637 espTm1637Player1(6, GPIO_NUM_18, GPIO_NUM_14);
    EspTm1637 espTm1637Player2(6, GPIO_NUM_18, GPIO_NUM_27);
    EspTm1637 espTm1637CentralDisplay(4, GPIO_NUM_18, GPIO_NUM_13);

    MenuSimulator simulator(espRtos, espRtosQueue,
        espLcdDisplay, pinIo, espTm1637Player1, espTm1637Player2, espTm1637CentralDisplay);

    simulator.run();
}
