#pragma once

#include "../DomainModel.hpp"
#include "../../M30_Messages/Types.hpp"
#include <cstdint>

class PassiveBuzzerDeviceModel;

class PassiveBuzzer : public DomainModel
{
public:
    PassiveBuzzer(
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log);

    PassiveBuzzer(
        const PassiveBuzzer&) = delete;

    PassiveBuzzer& operator=(
        const PassiveBuzzer&) = delete;

    PassiveBuzzer(
        PassiveBuzzer&&) = delete;

    PassiveBuzzer& operator=(
        PassiveBuzzer&&) = delete;

    ~PassiveBuzzer() override = default;

    void SetDeviceModel(
        IDeviceModel& deviceModel) override;

    void SetFrequency(
        uint32_t frequency);

    [[nodiscard]] uint32_t GetFrequency() const;

    void Start();

    void Stop();

    [[nodiscard]] bool IsPlaying() const;

    [[nodiscard]] PassiveBuzzerDeviceModel& GetPassiveBuzzerDeviceModel();

private:
    PassiveBuzzerDeviceModel* _passiveBuzzerDeviceModel;

    uint32_t _frequency;
    
    bool _isPlaying;
};
