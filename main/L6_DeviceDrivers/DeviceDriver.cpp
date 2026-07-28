#include "DeviceDriver.hpp"
#include "../L9_Utilities/Assert/Assert.hpp"

DeviceDriver::DeviceDriver()
{
}

DeviceDriver::~DeviceDriver()
{
}

void DeviceDriver::SetDeviceModel(IDeviceModel& deviceModel)
{
    Assert::IsNotNullptr(_deviceModel, "_deviceModel");
    _deviceModel = &deviceModel;
}

IDeviceModel& DeviceDriver::GetDeviceModel() const
{
    return *_deviceModel;
}
