#pragma once

class IDeviceModel;

class IDeviceDriver
{
public:
    virtual void Initialize() = 0;
    virtual void SetDeviceModel(IDeviceModel& deviceModel) = 0;
    virtual IDeviceModel& GetDeviceModel() const = 0;
};
