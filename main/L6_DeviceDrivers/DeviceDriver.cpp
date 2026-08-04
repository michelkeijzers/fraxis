#include "DeviceDriver.hpp"
#include "../L9_Utilities/Assert/Assert.hpp"

DeviceDriver::DeviceDriver()
: _deviceModel(nullptr)
{
}

void DeviceDriver::SetDeviceModel(
    IDeviceModel& deviceModel)
{
    _deviceModel = &deviceModel;
}

IDeviceModel& DeviceDriver::GetDeviceModel() const
{
    return *_deviceModel;
}
