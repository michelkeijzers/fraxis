#include "DacDeviceModel.hpp"

DacDeviceModel::DacDeviceModel()
: 
    _i2sPort(0)
{
}

// Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
DacDeviceModel::~DacDeviceModel() = default;

void DacDeviceModel::Initialize()
{
}

uint8_t DacDeviceModel::GetI2sPort() const
{
    return _i2sPort;
}

void DacDeviceModel::SetI2sPort(
    uint8_t port)
{
    _i2sPort = port;
}
