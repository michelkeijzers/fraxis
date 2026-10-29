#pragma once

#include "../M90_Utilities/Dirty/Dirty.hpp"
#include "../M90_Utilities/Initializable/Initializable.hpp"

class IDeviceModel : public Dirty, public Initializable
{
public:
    IDeviceModel();

    IDeviceModel(const IDeviceModel&) = delete;
    IDeviceModel& operator=(const IDeviceModel&) = delete;
    IDeviceModel(IDeviceModel&&) = delete;
    IDeviceModel& operator=(IDeviceModel&&) = delete;

    ~IDeviceModel() override;
};
