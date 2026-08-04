#pragma once

#include "IDeviceDriver.hpp"

class DeviceDriver : public IDeviceDriver
{
public:
    DeviceDriver();
    ~DeviceDriver() = default;

    void SetDeviceModel(
        IDeviceModel& deviceModel) override;
    IDeviceModel& GetDeviceModel() const override;

private:
    IDeviceModel* _deviceModel;
};
