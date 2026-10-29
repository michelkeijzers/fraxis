#pragma once

class IDeviceModel;

class IDomainModel
{
public:
    IDomainModel() = default;

    IDomainModel(const IDomainModel&) = delete;
    IDomainModel& operator=(const IDomainModel&) = delete;
    IDomainModel(IDomainModel&&) = delete;
    IDomainModel& operator=(IDomainModel&&) = delete;

    virtual ~IDomainModel() = default;

    virtual void SetDeviceModel(
        IDeviceModel& deviceModel) = 0;
};
