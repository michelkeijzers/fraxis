#include "DeviceDriver.hpp"
#include "../M90_Utilities/Assert/Assert.hpp"

DeviceDriver::DeviceDriver()
: _deviceModel(nullptr)
{
}

// Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
DeviceDriver::~DeviceDriver() = default;

void DeviceDriver::SetDeviceModel(
    IDeviceModel& deviceModel)
{
    _deviceModel = &deviceModel;
}

IDeviceModel& DeviceDriver::GetDeviceModel() const
{
    return *_deviceModel;
}
