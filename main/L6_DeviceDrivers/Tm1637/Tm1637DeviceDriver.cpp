#include "Tm1637DeviceDriver.hpp"
#include "../../L5_DeviceModels/Tm1637/Tm1637DeviceModel.hpp"
#include "../../L8_Services/Gpio/Gpio.hpp"
#include "../../L9_Utilities/Assert/Assert.hpp"

Tm1637DeviceDriver::Tm1637DeviceDriver()
:   _clockPin(0), 
    _dataPin(0), 
    _gpio(nullptr)
{
}

Tm1637DeviceDriver::~Tm1637DeviceDriver()
{
}

void Tm1637DeviceDriver::SetGpio(
    Gpio& gpio)
{
    _gpio = &gpio;
}

void Tm1637DeviceDriver::SetPinsConfiguration(
    uint8_t clockPin, 
    uint8_t dataPin)
{
    Assert::IsEsp32Pin(clockPin, "Clock pin");
    Assert::IsEsp32Pin(dataPin, "Data pin");

    _clockPin = clockPin;
    _dataPin = dataPin;
}

void Tm1637DeviceDriver::Initialize()
{
    Assert::IsTrue(GetGpio().ConfigAsOutput(_clockPin), "Clock pin config");
    Assert::IsTrue(GetGpio().ConfigAsOutput(_dataPin), "Data pin config");

    Assert::IsTrue(GetGpio().SetLevel(_clockPin, true), "Clock pin set level");
    Assert::IsTrue(GetGpio().SetLevel(_dataPin, true), "Data pin set level");
}

Gpio& Tm1637DeviceDriver::GetGpio()
{
    return *_gpio;
}

void Tm1637DeviceDriver::SendToDisplay()
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

void Tm1637DeviceDriver::Start()
{
    Assert::IsTrue(GetGpio().SetLevel(_dataPin, true), "Clock pin set level high");
    Assert::IsTrue(GetGpio().SetLevel(_clockPin, true), "Clock pin set level");
    GetGpio().DelayUs(3);

    Assert::IsTrue(GetGpio().SetLevel(_dataPin, false), "Data pin set level low");
    GetGpio().DelayUs(3);
}

void Tm1637DeviceDriver::WriteByte(
    uint8_t data)
{
    // Send 8 bits, LSB first
    for (int index = 0; index < 8; index++)
    {
        Assert::IsTrue(GetGpio().SetLevel(_clockPin, false), "Clock pin set level low");
        GetGpio().DelayUs(3);

        Assert::IsTrue(GetGpio().SetLevel(_dataPin, (data >> index) & 0x01), "Data pin set level");
        GetGpio().DelayUs(3);

        Assert::IsTrue(GetGpio().SetLevel(_clockPin, true), "Clock pin set level high");
        GetGpio().DelayUs(3);
    }
}

void Tm1637DeviceDriver::Stop()
{
    Assert::IsTrue(GetGpio().SetLevel(_clockPin, false), "Clock pin set level low");
    GetGpio().DelayUs(3);

    Assert::IsTrue(GetGpio().SetLevel(_dataPin, false), "Data pin set level low");
    GetGpio().DelayUs(3);

    Assert::IsTrue(GetGpio().SetLevel(_clockPin, true), "Clock pin set level high");
    GetGpio().DelayUs(3);

    Assert::IsTrue(GetGpio().SetLevel(_dataPin, true), "Data pin set level high");
    GetGpio().DelayUs(3);
}
