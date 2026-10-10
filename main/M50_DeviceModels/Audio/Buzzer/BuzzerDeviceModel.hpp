#pragma once

#include "../../M60_DeviceDrivers/Audio/Buzzer/BuzzerDeviceDriver.hpp"
#include "../DeviceModel.hpp"
#include <cstdint>

class BuzzerDeviceModel : public DeviceModel
{
public:
    BuzzerDeviceModel();
    ~BuzzerDeviceModel() = default;

    void Initialize() override;

    uint8_t GetPwmPin() const;
    void SetPwmPin(
        uint8_t pwmPin);

    uint32_t GetFrequency() const;
    void SetFrequency(
        uint32_t frequency);

    bool IsPlaying() const;
    void SetPlaying(
        bool playing);

private:
    uint8_t _pwmPin;
    uint32_t _frequency;
    bool _isPlaying;
};
