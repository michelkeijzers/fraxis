#include "EspTm1637Driver.hpp"
#include "Tm1637Model.hpp"
#include <cstdint>
#include "esp_rom_sys.h"

EspTm1637Driver::EspTm1637Driver(Tm1637Model& model, gpio_num_t clkPin, gpio_num_t dioPin)
    : Tm1637Driver(model), _clkPin(clkPin), _dioPin(dioPin)
{
}

void EspTm1637Driver::Initialize()
{
    gpio_config_t cfg = {
        .pin_bit_mask = (1ULL << _clkPin) | (1ULL << _dioPin),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&cfg);

    gpio_set_level(_clkPin, 1);
    gpio_set_level(_dioPin, 1);    
}

void EspTm1637Driver::Write()
{
    Start();

    // Command: set data command (automatic address increment)
    WriteByte(0x40);

    Stop();
    Start();

    // Command: set starting address to 0
    WriteByte(0xC0);

    // Write all segment bytes
    for (uint8_t i = 0; i < _model.GetNumberOfDigits(); i++)
    {
        WriteByte(_model.EncodeDigitNr(i));
    }
    Stop();

    // Brightness command (0x88–0x8F)
    Start();
    WriteByte(0x88 | _model.GetBrightness());
    Stop();
}

void EspTm1637Driver::Start()
{
    gpio_set_level(_dioPin, 1);
    gpio_set_level(_clkPin, 1);
    esp_rom_delay_us(5);

    gpio_set_level(_dioPin, 0);
    esp_rom_delay_us(5);
}

void EspTm1637Driver::Stop()
{
    gpio_set_level(_clkPin, 0);
    esp_rom_delay_us(5);

    gpio_set_level(_dioPin, 0);
    esp_rom_delay_us(5);

    gpio_set_level(_clkPin, 1);
    esp_rom_delay_us(5);

    gpio_set_level(_dioPin, 1);
    esp_rom_delay_us(5);
}

void EspTm1637Driver::WriteByte(uint8_t data)
{
    // Send 8 bits, LSB first
    for (int i = 0; i < 8; i++)
    {
        gpio_set_level(_clkPin, 0);
        esp_rom_delay_us(3);

        gpio_set_level(_dioPin, (data >> i) & 0x01);
        esp_rom_delay_us(3);

        gpio_set_level(_clkPin, 1);
        esp_rom_delay_us(3);
    }
}