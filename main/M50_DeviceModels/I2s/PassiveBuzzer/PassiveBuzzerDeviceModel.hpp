#pragma once

#include "../../../M60_DeviceDrivers/I2s/PassiveBuzzer/PassiveBuzzerDeviceDriver.hpp"
#include "../../DeviceModel.hpp"
#include <cstdint>

namespace M90::Assert
{
    class IAssert;
}

namespace M90::String
{
    class IStringUtilities;
}

class PassiveBuzzerDeviceModel : public DeviceModel
{
public:
    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    PassiveBuzzerDeviceModel(
        M90::Assert::IAssert& assert,
        M90::String::IStringUtilities& stringUtilities);

    PassiveBuzzerDeviceModel(
        const PassiveBuzzerDeviceModel&) = delete;
    
    PassiveBuzzerDeviceModel& operator=(const
        PassiveBuzzerDeviceModel&) = delete;
    
    PassiveBuzzerDeviceModel(
        PassiveBuzzerDeviceModel&&) = delete;
    
    PassiveBuzzerDeviceModel& operator=(
        PassiveBuzzerDeviceModel&&) = delete;

    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    ~PassiveBuzzerDeviceModel() override;

    void Initialize() override;

    [[nodiscard]] uint8_t GetPwmPin() const;
    
    void SetPwmPin(
        uint8_t pwmPin);

    [[nodiscard]] uint32_t GetFrequency() const;
    
    void SetFrequency(
        uint32_t frequency);

    [[nodiscard]] bool IsPlaying() const;
    
    void SetPlaying(
        bool playing);

private:
    uint8_t _pwmPin;
    
    uint32_t _frequency;
    
    bool _isPlaying;
};
