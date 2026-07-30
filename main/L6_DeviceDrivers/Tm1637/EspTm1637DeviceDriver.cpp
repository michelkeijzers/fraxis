#ifdef ESP_PLATFORM

#include "EspTm1637DeviceDriver.hpp"
#include "esp_rom_sys.h"
#include "../../L5_DeviceModels/Tm1637/Tm1637DeviceModel.hpp"
#include "../../L9_Utilities/Assert/Assert.hpp"

EspTm1637DeviceDriver::EspTm1637DeviceDriver()
{
}

EspTm1637DeviceDriver::~EspTm1637DeviceDriver()
{
}

void EspTm1637DeviceDriver::SetPinsConfiguration(uint8_t clockPin, uint8_t dataPin)
{
    _clockPin = static_cast<gpio_num_t>(clockPin);
    _dataPin = static_cast<gpio_num_t>(dataPin);
}

void EspTm1637DeviceDriver::Initialize()
{
    gpio_config_t cfg = {
        .pin_bit_mask = (1ULL << _clockPin) | (1ULL << _dataPin),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    Assert::Equals(gpio_config(&cfg), ESP_OK, "Failed to configure GPIO");
    Assert::Equals(gpio_set_level(_clockPin, 1), ESP_OK, "Failed to set clock pin level");
    Assert::Equals(gpio_set_level(_dataPin, 1), ESP_OK, "Failed to set data pin level");
}

void EspTm1637DeviceDriver::SendToDisplay()
{

    auto& tm1637DeviceModel = static_cast<Tm1637DeviceModel&>(GetDeviceModel());

    Start();
    WriteByte(0x40);
    Stop();

    for (uint8_t index = 0; index < tm1637DeviceModel.GetNrOfDigits(); index++)
    {
        if (tm1637DeviceModel.IsCharacterDirty(index))
        {
            Start();
            WriteByte(0xC0 | index); // Address
            WriteByte(tm1637DeviceModel.GetCharacter(index));
            Stop();
        }
    }

    Start();
    WriteByte(0x88 | Tm1637DeviceModel::BRIGHTNESS);
    Stop();

    tm1637DeviceModel.ClearDirty();
}

void EspTm1637DeviceDriver::Start()
{
    Assert::Equals(gpio_set_level(_dataPin, 1), ESP_OK, "Failed to set data pin level");
    Assert::Equals(gpio_set_level(_clockPin, 1), ESP_OK, "Failed to set clock pin level");
    esp_rom_delay_us(3);

    Assert::Equals(gpio_set_level(_dataPin, 0), ESP_OK, "Failed to set data pin level");
    esp_rom_delay_us(3);
}

void EspTm1637DeviceDriver::Stop()
{
    Assert::Equals(gpio_set_level(_clockPin, 0), ESP_OK, "Failed to set clock pin level");
    esp_rom_delay_us(3);

    Assert::Equals(gpio_set_level(_dataPin, 0), ESP_OK, "Failed to set data pin level");
    esp_rom_delay_us(3);

    Assert::Equals(gpio_set_level(_clockPin, 1), ESP_OK, "Failed to set clock pin level");
    esp_rom_delay_us(3);

    Assert::Equals(gpio_set_level(_dataPin, 1), ESP_OK, "Failed to set data pin level");
    esp_rom_delay_us(3);
}

void EspTm1637DeviceDriver::WriteByte(uint8_t data)
{
    // Send 8 bits, LSB first
    for (int index = 0; index < 8; index++)
    {
        Assert::Equals(gpio_set_level(_clockPin, 0), ESP_OK, "Failed to set clock pin level");
        esp_rom_delay_us(3);

        Assert::Equals(gpio_set_level(_dataPin, (data >> index) & 0x01), ESP_OK, "Failed to set data pin level");
        esp_rom_delay_us(3);

        Assert::Equals(gpio_set_level(_clockPin, 1), ESP_OK, "Failed to set clock pin level");
        esp_rom_delay_us(3);
    }
}

#endif // ESP_PLATFORM
