#include "I2sDac.hpp"
#include "../../../M50_DeviceModels/I2s/Max53987a/Max53987aDeviceModel.hpp"

I2sDac::I2sDac(
    M50::I2s::Max53987aDeviceModel& max53987aDeviceModel,
    M50::IDeviceModel& deviceModel,
    M90::Assert::IAssert& assert,
    M90::Log::ILog& log)
: 
    DomainModel(deviceModel, assert, log),
    _max53987aDeviceModel(max53987aDeviceModel)
{
    // No functionality required.
}

void I2sDac::WriteSamples( // NOSONAR S5817: const
    const int16_t* /* buffer */,
    size_t /* length */)
{
    // NOSONAR TODO I2S
}

M50::I2s::Max53987aDeviceModel& I2sDac::GetMax53987aDeviceModel()
{
    return _max53987aDeviceModel;
}
