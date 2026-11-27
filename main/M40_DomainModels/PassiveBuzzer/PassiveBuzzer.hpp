#pragma once

#include "../DomainModel.hpp"
#include "../../M30_Messages/Types.hpp"
#include <cstdint>

namespace M50::PassiveBuzzer
{
    class PassiveBuzzerDeviceModel;
}

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
        M50::IDeviceModel& deviceModel) override;

    void SetFrequency(
        uint32_t frequency);

    [[nodiscard]] uint32_t GetFrequency() const;

    void Start();

    void Stop();

    [[nodiscard]] bool IsPlaying() const;

    [[nodiscard]] M50::PassiveBuzzer::PassiveBuzzerDeviceModel& GetPassiveBuzzerDeviceModel();

private:
    M50::PassiveBuzzer::PassiveBuzzerDeviceModel* _passiveBuzzerDeviceModel;

    uint32_t _frequency;
    
    bool _isPlaying;
};
