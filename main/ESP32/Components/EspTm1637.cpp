#include "EspTm1637.hpp"
#include "esp_rom_sys.h"

EspTm1637::EspTm1637(uint8_t nrOfDigits, gpio_num_t clkPin, gpio_num_t dioPin)
    : Tm1637(nrOfDigits), _clkPin(clkPin), _dioPin(dioPin) 
{
}

EspTm1637::~EspTm1637()
{
}

void EspTm1637::Initialize()
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

void EspTm1637::Update()
{
}

void EspTm1637::Write()
{
    Start();

    // Command: set data command (automatic address increment)
    WriteByte(0x40);

    Stop();
    Start();

    // Command: set starting address to 0
    WriteByte(0xC0);

    // Write all segment bytes
    for (uint8_t i = 0; i < _numberOfDigits; i++)
    {
        WriteByte(EncodeDigitNr(i));
    }
    Stop();

    // Brightness command (0x88–0x8F)
    Start();
    WriteByte(0x88 | _brightness);
    Stop();
}

void EspTm1637::Start()
{
    gpio_set_level(_dioPin, 1);
    gpio_set_level(_clkPin, 1);
    esp_rom_delay_us(5);

    gpio_set_level(_dioPin, 0);
    esp_rom_delay_us(5);
}

void EspTm1637::Stop()
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

void EspTm1637::WriteByte(uint8_t data)
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