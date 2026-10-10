#pragma once

#include "../../DomainModel.hpp"
#include "../../../M30_Messages/Types.hpp"
#include <cstdint>

class BuzzerDeviceModel;

class Buzzer : public DomainModel
{
public:
    Buzzer();
    ~Buzzer() = default;

    void SetDeviceModel(
        IDeviceModel& deviceModel) override;

    void SetFrequency(
        uint32_t frequency);

    uint32_t GetFrequency() const;

    void Start();
    void Stop();

    bool IsPlaying() const;

    BuzzerDeviceModel& GetBuzzerDeviceModel();

private:
    BuzzerDeviceModel* _buzzerDeviceModel;
    uint32_t _frequency;
    bool _isPlaying;
};
