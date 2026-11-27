#pragma once

#include "../DomainModel.hpp"
#include <cstdint>

namespace M50::SevenSegmentsDisplays
{
    class Tm1637DeviceModel;
}

class Tm1637 : public DomainModel
{
public:
    Tm1637(
        M50::SevenSegmentsDisplays::Tm1637DeviceModel& tm1637DeviceModel,
        M50::IDeviceModel& deviceModel,
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log);

    Tm1637(
        const Tm1637&) = delete;

    Tm1637& operator=(
        const Tm1637&) = delete;

    Tm1637(
        Tm1637&&) = delete;
    
    Tm1637& operator=(
        Tm1637&&) = delete;

    ~Tm1637() override = default;

    M50::SevenSegmentsDisplays::Tm1637DeviceModel& GetTm1637DeviceModel();

    void Enable(
        bool enable);

    void SetBrightness(
        uint8_t brightness);

    void SetValue(
        uint32_t value);

    void SetTime(
        uint8_t first, 
        uint8_t second);

private:
    enum EFormat : uint8_t
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

    M50::SevenSegmentsDisplays::Tm1637DeviceModel& _tm1637DeviceModel;
};
