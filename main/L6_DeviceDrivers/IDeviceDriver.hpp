#pragma once

#include "../L9_Utilities/Initializable/Initializable.hpp"

class IDeviceModel;

class IDeviceDriver : public Initializable
{
public:
    virtual void SetDeviceModel(IDeviceModel& deviceModel) = 0;
    virtual IDeviceModel& GetDeviceModel() const = 0;
};
