#pragma once

class IDeviceModel;

class IDomainModel
{
public:
    virtual void SetDeviceModel(IDeviceModel& deviceModel) = 0;
};
