#pragma once

#include "../L9_Utilities/Initializable/Initializable.hpp"

class IDeviceModel : public Initializable
{
public:
    IDeviceModel();
    virtual ~IDeviceModel();
};
