#include "DeviceDriver.hpp"
#include "../M90_Utilities/Assert/IAssert.hpp"

namespace M60
{
    DeviceDriver::DeviceDriver(
        M90::Assert::IAssert& assert)
    : 
        IDeviceDriver(),
        _assert(assert),
        _deviceModel(nullptr)
    {
        // No actions required.
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

    M90::Assert::IAssert& DeviceDriver::GetAssert() const
    {
        return _assert;
    }
}
