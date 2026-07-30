#pragma once

#include "IDeviceModel.hpp"
#include "../L9_Utilities/Dirty/Dirty.hpp"

class DeviceModel : public IDeviceModel, public Dirty
{
public:
    DeviceModel();
    virtual ~DeviceModel();
};
