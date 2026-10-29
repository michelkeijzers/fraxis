#pragma once

#include "../../DomainModel.hpp"
#include "../../../M30_Messages/Types.hpp"
#include <cstdint>

class BuzzerDeviceModel;

class Buzzer : public DomainModel
{
public:
    Buzzer();

    Buzzer(const Buzzer&) = delete;
    Buzzer& operator=(const Buzzer&) = delete;
    Buzzer(Buzzer&&) = delete;
    Buzzer& operator=(Buzzer&&) = delete;

    ~Buzzer() override = default;

    void SetDeviceModel(
        IDeviceModel& deviceModel) override;

    void SetFrequency(
        uint32_t frequency);

    [[nodiscard]] uint32_t GetFrequency() const;

    void Start();
    void Stop();

    [[nodiscard]] bool IsPlaying() const;

    [[nodiscard]] BuzzerDeviceModel& GetBuzzerDeviceModel();

private:
    BuzzerDeviceModel* _buzzerDeviceModel;
    uint32_t _frequency;
    bool _isPlaying;
};
