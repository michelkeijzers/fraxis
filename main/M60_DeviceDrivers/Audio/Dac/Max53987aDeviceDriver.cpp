#include "Max53987aDeviceDriver.hpp"
#include "../../../M90_Utilities/Assert/Assert.hpp"
#include "../../../M30_Messages/Types.hpp"

Max53987aDeviceDriver::Max53987aDeviceDriver()
{
}

size_t Max53987aDeviceDriver::WriteSamples(
    const int16_t* buffer,
    size_t length)
{
    size_t bytesToWrite = length * sizeof(int16_t);
    size_t bytesWritten = Write(buffer, bytesToWrite, 100);
    return bytesWritten / sizeof(int16_t);
}
