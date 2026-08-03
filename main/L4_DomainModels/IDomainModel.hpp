#pragma once

class IDeviceModel;

class IDomainModel
{
public:
    IDomainModel();
    virtual ~IDomainModel();

    virtual void SetDeviceModel(
        IDeviceModel& deviceModel) = 0;
};
