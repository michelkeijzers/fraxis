#pragma once

#include "../../../DomainModel.hpp"

class Tm1637DeviceModel;

class Tm1637DeviceModel;

class Tm1637 : public DomainModel
{
public:
    Tm1637();
    ~Tm1637() = default;

    void SetDeviceModel(IDeviceModel& deviceModel) override;

private:
    Tm1637DeviceModel* _tm1637DeviceModel;
};
