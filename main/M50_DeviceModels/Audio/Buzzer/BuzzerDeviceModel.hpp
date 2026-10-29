#pragma once

#include "../../../M60_DeviceDrivers/Audio/Buzzer/BuzzerDeviceDriver.hpp"
#include "../../DeviceModel.hpp"
#include <cstdint>

class BuzzerDeviceModel : public DeviceModel
{
public:
    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    BuzzerDeviceModel();

    BuzzerDeviceModel(const BuzzerDeviceModel&) = delete;
    BuzzerDeviceModel& operator=(const BuzzerDeviceModel&) = delete;
    BuzzerDeviceModel(BuzzerDeviceModel&&) = delete;
    BuzzerDeviceModel& operator=(BuzzerDeviceModel&&) = delete;

    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    ~BuzzerDeviceModel() override;

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
