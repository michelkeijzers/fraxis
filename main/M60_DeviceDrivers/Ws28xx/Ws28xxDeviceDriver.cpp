#include "Ws28xxDeviceDriver.hpp"
#include "Ws2812Rmt.hpp"
#include "../../M50_DeviceModels/Ws28xx/Ws28xxDeviceModel.hpp"
#include <vector>

namespace M60::Ws28xx
{
    Ws28xxDeviceDriver::Ws28xxDeviceDriver(
        uint16_t numberOfLeds,
        IWs2812Rmt& ws2812Rmt,
        M90::Assert::IAssert& assert,
        M90::String::IStringUtilities& stringUtilities)
    :
        DeviceDriver(assert, stringUtilities),
        _numberOfLeds(numberOfLeds),
        _ws2812Rmt(ws2812Rmt)
    {
        // No actions required.
    }

    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    Ws28xxDeviceDriver::~Ws28xxDeviceDriver() = default;

    void Ws28xxDeviceDriver::Initialize()
    {
        _ws2812Rmt.Initialize();
    }

    void Ws28xxDeviceDriver::SetWs28xxDeviceModel(
        M50::Ws28xx::IWs28xxDeviceModel& ws28xxDeviceModel)
    {
        _ws28xxDeviceModel = &ws28xxDeviceModel;
    }

    M50::Ws28xx::IWs28xxDeviceModel& Ws28xxDeviceDriver::GetWs28xxDeviceModel()
    {
        return *_ws28xxDeviceModel;
    }

    void Ws28xxDeviceDriver::WriteToLedStrip()
    {
        std::vector<M50::Ws28xx::Ws28xxDeviceModel::RgbStruct> destinationBuffer(_numberOfLeds);
        GetWs28xxDeviceModel().FillGrbBufferToSend(destinationBuffer);
        _ws2812Rmt.Send(reinterpret_cast<const unsigned char*>( // NOSONAR ESP32 prefers char*
            destinationBuffer.data()));
    }
}
