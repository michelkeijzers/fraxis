#include "Inmp1441DeviceDriver.hpp"
#include "../../../M90_Utilities/Assert/Assert.hpp"
#include "../../../M30_Messages/Types.hpp"

Inmp1441DeviceDriver::Inmp1441DeviceDriver()
: _isRecording(false)
{
}

void Inmp1441DeviceDriver::StartRecording()
{
    _isRecording = true;
    Start();
}

void Inmp1441DeviceDriver::StopRecording()
{
    _isRecording = false;
    Stop();
}

size_t Inmp1441DeviceDriver::ReadSamples(
    int16_t* buffer,
    size_t length)
{
    if (!_isRecording)
    {
        return 0;
    }

    size_t bytesToRead = length * sizeof(int16_t);
    size_t bytesRead = Read(buffer, bytesToRead, 100);
    return bytesRead / sizeof(int16_t);
}
