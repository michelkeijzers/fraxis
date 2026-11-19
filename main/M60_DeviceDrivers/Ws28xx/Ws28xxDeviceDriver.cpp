#include "Ws28xxDeviceDriver.hpp"
#include "Ws2812Rmt.hpp"
#include "../../M50_DeviceModels/Ws28xx/Ws28xxDeviceModel.hpp"
#include <vector>

#include "../../M90_Utilities/Assert/Assert.hpp"
#include "../../M90_Utilities/Log/Log.hpp" 
#include "../../M90_Utilities/Time/TimeUtilities.hpp"

namespace M60::Ws28xx
{
    Ws28xxDeviceDriver::Ws28xxDeviceDriver(
        M90::Assert::IAssert& assert,
        M90::String::IStringUtilities& stringUtilities)
    :
        DeviceDriver(assert, stringUtilities),
        _dataPin(0),
        _numberOfLeds(0),
        _rmt(nullptr)
    {
        // No actions required.
    }

    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    Ws28xxDeviceDriver::~Ws28xxDeviceDriver() = default;

    uint8_t Ws28xxDeviceDriver::GetDataPin() const
    {
        return _dataPin;
    }

    void Ws28xxDeviceDriver::SetDataPin(
        uint8_t dataPin)
    {
        _dataPin = dataPin;
    }

    void Ws28xxDeviceDriver::SetRmt(
        M80::Rmt::IRmt& rmt)
    {
        _rmt = &rmt;
    }

    void Ws28xxDeviceDriver::Initialize()
    {
        _numberOfLeds = GetWs28xxDeviceModel().GetNumberOfLeds();
        _ws2812rmt = std::make_unique<Ws2812Rmt>(GetAssert(), _dataPin, _numberOfLeds, *_rmt);
        _ws2812rmt->Initialize();
    }

    Ws28xxDeviceModel& Ws28xxDeviceDriver::GetWs28xxDeviceModel()
    {
        return static_cast<Ws28xxDeviceModel&>(GetDeviceModel());
    }

    void Ws28xxDeviceDriver::WriteToLedStrip()
    {
        std::vector<Ws28xxDeviceModel::RgbStruct> destinationBuffer(_numberOfLeds);
        GetWs28xxDeviceModel().FillGrbBufferToSend(destinationBuffer);
        _ws2812rmt->Send(reinterpret_cast<const unsigned char*>( // NOSONAR ESP32 prefers char*
            destinationBuffer.data()));
    }
}
