#pragma once

#include "../M90_Utilities/Initializable/Initializable.hpp"

namespace M90::Assert
{
    class IAssert;
}

class IDeviceModel;

namespace M60
{
    class IDeviceDriver : public M90::Initializable::Initializable
    {
    public:
        ~IDeviceDriver() = default;

        virtual void SetDeviceModel(
            IDeviceModel& deviceModel) = 0;

        [[nodiscard]] virtual IDeviceModel& GetDeviceModel() const = 0;

        [[nodiscard]] virtual M90::Assert::IAssert& GetAssert() const = 0;

protected:
        IDeviceDriver() = default;

        IDeviceDriver(const IDeviceDriver &) = default;

        IDeviceDriver &operator=(const IDeviceDriver &) = default;

        IDeviceDriver(IDeviceDriver &&) = default;

        IDeviceDriver &operator=(IDeviceDriver &&) = default;
    };
}
