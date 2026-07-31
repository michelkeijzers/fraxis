#pragma once

#include "../L9_Utilities/Dirty/Dirty.hpp"
#include "../L9_Utilities/Initializable/Initializable.hpp"

class IDeviceModel : public Dirty, public Initializable
{
public:
    IDeviceModel();
    virtual ~IDeviceModel();
};
