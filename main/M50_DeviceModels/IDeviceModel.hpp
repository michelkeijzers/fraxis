#pragma once

#include "../M90_Utilities/Dirty/Dirty.hpp"
#include "../M90_Utilities/Initializable/Initializable.hpp"

class IDeviceModel : public M90::Dirty::Dirty, public M90::Initializable::Initializable
{
public:
    IDeviceModel() = default;

    IDeviceModel(const IDeviceModel&) = delete;
    IDeviceModel& operator=(const IDeviceModel&) = delete;
    IDeviceModel(IDeviceModel&&) = delete;
    IDeviceModel& operator=(IDeviceModel&&) = delete;

    ~IDeviceModel() override = default;
};
