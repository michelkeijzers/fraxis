#include "Max53987aDeviceModel.hpp"

Max53987aDeviceModel::Max53987aDeviceModel(
    M90::Assert::IAssert& assert,
    M90::Log::ILog& log,
    M90::String::IStringUtilities& stringUtilities)
: 
    DeviceModel(assert, log, stringUtilities),
    _i2sPort(0)
{
    // No functionality required.
}

// Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
Max53987aDeviceModel::~Max53987aDeviceModel() = default;

void Max53987aDeviceModel::Initialize()
{
}

uint8_t Max53987aDeviceModel::GetI2sPort() const
{
    return _i2sPort;
}

void Max53987aDeviceModel::SetI2sPort(
    uint8_t port)
{
    _i2sPort = port;
}
