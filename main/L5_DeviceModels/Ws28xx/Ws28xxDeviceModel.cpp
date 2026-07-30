#include "Ws28xxDeviceModel.hpp"
#include "GrbBufferFiller.hpp"
#include "../../L9_Utilities/Assert/Assert.hpp"

Ws28xxDeviceModel::Ws28xxDeviceModel()
{
}

Ws28xxDeviceModel::~Ws28xxDeviceModel()
{
}

uint16_t Ws28xxDeviceModel::GetNrOfLeds() const
{
    return _nrOfLeds;
}

void Ws28xxDeviceModel::SetNrOfLeds(uint16_t nrOfLeds)
{
    _nrOfLeds = nrOfLeds;
}

void Ws28xxDeviceModel::SetMaxCurrentConsumption(uint16_t maxCurrentConsumption)
{
    _maxCurrentConsumption = maxCurrentConsumption;
}

/// @brief  Allocates memory for leds.
void Ws28xxDeviceModel::Initialize()
{
    Assert::Equals(sizeof(RgbStruct), 3, "GRB struct must be 3 bytes");

    _leds.reset(new RgbStruct[_nrOfLeds]);
}

void Ws28xxDeviceModel::SetPixel(uint16_t index, uint8_t red, uint8_t green, uint8_t blue)
{
    if (!Ws28xxDeviceModel::IsRgbEqual(_leds[index], CreateRgb(red, green, blue)))
    {
            _leds[index] = CreateRgb(red, green, blue);
            MarkDirty();
    }
}

/* static */ bool Ws28xxDeviceModel::IsRgbEqual(RgbStruct a, RgbStruct b)
{
    return a.red == b.red && a.green == b.green && a.blue == b.blue;
}

Ws28xxDeviceModel::RgbStruct Ws28xxDeviceModel::CreateRgb(uint8_t red, uint8_t green, uint8_t blue) const
{
    return { red, green, blue };
}

void Ws28xxDeviceModel::FillGrbBufferToSend(RgbStruct* grbBuffer)
{
    GrbBufferFiller filler(_leds.get(), _nrOfLeds, grbBuffer, _maxCurrentConsumption);
    filler.Run();
}

