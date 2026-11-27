#include "Max53987aDeviceDriver.hpp"
#include "../../../M90_Utilities/Assert/IAssert.hpp"
#include "../../../M30_Messages/Types.hpp"

namespace M60::I2s
{
    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    Max53987aDeviceDriver::Max53987aDeviceDriver(
        M90::Assert::IAssert& assert,
        M90::String::IStringUtilities& stringUtilities)
    :
        I2sDeviceDriver(assert, stringUtilities)
    {
        // No functionality required.
    }

    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    Max53987aDeviceDriver::~Max53987aDeviceDriver() = default;

    void Max53987aDeviceDriver::SetMax53987aDeviceModel(
        M50::I2s::IMax53987aDeviceModel& max53987aDeviceModel)
    {
        _max53987aDeviceModel = &max53987aDeviceModel;
    }

    M50::I2s::IMax53987aDeviceModel& Max53987aDeviceDriver::GetMax53987aDeviceModel()
    {
        return *_max53987aDeviceModel;
    }

    size_t Max53987aDeviceDriver::WriteSamples(
        const int16_t* buffer,
        size_t length)
    {
        size_t bytesToWrite = length * sizeof(int16_t);
        size_t bytesWritten = Write(buffer, bytesToWrite, 100);
        return bytesWritten / sizeof(int16_t);
    }
}