#pragma once

#include "../M90_Utilities/Initializable/Initializable.hpp"

class IDeviceModel;

class IDeviceDriver : public Initializable
{
public:
    IDeviceDriver();

    IDeviceDriver(const IDeviceDriver&) = delete;
    IDeviceDriver& operator=(const IDeviceDriver&) = delete;
    IDeviceDriver(IDeviceDriver&&) = delete;
    IDeviceDriver& operator=(IDeviceDriver&&) = delete;

    ~IDeviceDriver() override;

    virtual void SetDeviceModel(
        IDeviceModel& deviceModel) = 0;
    
    [[nodiscard]] virtual IDeviceModel& GetDeviceModel() const = 0;
};
