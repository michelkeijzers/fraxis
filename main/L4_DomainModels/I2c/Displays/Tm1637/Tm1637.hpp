#pragma once

#include "../../../DomainModel.hpp"
#include <cstdint>

class Tm1637DeviceModel;

class Tm1637 : public DomainModel
{
public:
    Tm1637();
    ~Tm1637() = default;

    void SetDeviceModel(IDeviceModel& deviceModel) override;

    void SetValue(uint32_t value);
    void SetTime(uint8_t first, uint8_t second);

private:
    enum EFormat 
    {
        Value, 
        Time
    };

    EFormat _format;

    /// @brief Shows value in case of format Value.
    uint32_t _value;

    /// @brief Shows first two digits in case of format Time.
    uint8_t _first;
    /// @brief Shows second two digits in case of format Time.
    uint8_t _second;

    Tm1637DeviceModel* _tm1637DeviceModel;
};
