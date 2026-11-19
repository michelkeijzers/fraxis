#pragma once

#include "../M90_Utilities/Dirty/Dirty.hpp"
#include "../M90_Utilities/Initializable/Initializable.hpp"

namespace M90
{
    namespace Assert
    {
        class IAssert;
    }

    namespace String
    {
        class IStringUtilities;
    }
}

class IDeviceModel : public M90::Dirty::Dirty, public M90::Initializable::Initializable
{
public:
    IDeviceModel() = default;

    IDeviceModel(
        const IDeviceModel&) = delete;
    
    IDeviceModel& operator=(
        const IDeviceModel&) = delete;
    
    IDeviceModel(
        IDeviceModel&&) = delete;
    
    IDeviceModel& operator=(
        IDeviceModel&&) = delete;

    ~IDeviceModel() override = default;

    //virtual M90::Assert::IAssert &GetAssert() const = 0;

    //virtual M90::String::IStringUtilities& GetStringUtilities() const = 0;
};
