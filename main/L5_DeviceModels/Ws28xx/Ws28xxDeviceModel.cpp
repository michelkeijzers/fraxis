#include "Ws28xxDeviceModel.hpp"
#include "GrbBufferFiller.hpp"
#include "../../L9_Utilities/Assert/Assert.hpp"

Ws28xxDeviceModel::Ws28xxDeviceModel()
:   _leds{}, 
    _nrOfLeds(0),
    _maxCurrentConsumption(0),
    _frameReady(false)
{
}

Ws28xxDeviceModel::~Ws28xxDeviceModel()
{
}

uint16_t Ws28xxDeviceModel::GetNrOfLeds() const
{
    return _nrOfLeds;
}

void Ws28xxDeviceModel::SetNrOfLeds(
    uint16_t nrOfLeds)
{
    _nrOfLeds = nrOfLeds;
}

void Ws28xxDeviceModel::SetMaxCurrentConsumption(
    uint16_t maxCurrentConsumption)
{
    _maxCurrentConsumption = maxCurrentConsumption;
}

Ws28xxDeviceModel::RgbStruct* Ws28xxDeviceModel::GetLeds()
{
    return _leds.get();
}

/// @brief  Allocates memory for leds.
void Ws28xxDeviceModel::Initialize()
{
    Assert::Equals(Types::ETaskId::I2cTask, sizeof(RgbStruct), 3, "GRB struct must be 3 bytes");
    _leds.reset(new RgbStruct[_nrOfLeds] {} );
    MarkInitialized();
}

void Ws28xxDeviceModel::SetPixel(
    uint16_t index, 
    uint8_t red, 
    uint8_t green, 
    uint8_t blue)
{
    Assert::IsTrue(Types::ETaskId::I2cTask, IsInitialized());
    
    if (!Ws28xxDeviceModel::IsRgbEqual(_leds[index], CreateRgb(red, green, blue)))
    {
        _leds[index] = CreateRgb(red, green, blue);
        MarkDirty();
    }
}

void Ws28xxDeviceModel::SetFrameReady()
{
    _frameReady = true;
}

/* static */ bool Ws28xxDeviceModel::IsRgbEqual(RgbStruct a, RgbStruct b)
{
    return a.red == b.red && a.green == b.green && a.blue == b.blue;
}

Ws28xxDeviceModel::RgbStruct Ws28xxDeviceModel::CreateRgb(
    uint8_t red, 
    uint8_t green,
    uint8_t blue) const
{
    return { red, green, blue };
}

void Ws28xxDeviceModel::FillGrbBufferToSend(
    std::vector<Ws28xxDeviceModel::RgbStruct>& grbBuffer)
{
    Assert::IsTrue(Types::ETaskId::I2cTask, IsInitialized());

    if (_frameReady)
    {
        GrbBufferFiller filler(_leds.get(), _nrOfLeds, grbBuffer.data(), _maxCurrentConsumption);
        filler.Run();
        _frameReady = false;
    }
}

