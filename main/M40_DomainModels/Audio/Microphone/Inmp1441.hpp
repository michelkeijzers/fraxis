#pragma once

#include "../../DomainModel.hpp"
#include "../../../M30_Messages/Types.hpp"
#include <cstdint>
#include <vector>

class Inmp1441DeviceModel;

class Inmp1441 : public DomainModel
{
public:
    static constexpr uint32_t SAMPLE_RATE = 16000;
    static constexpr uint16_t BITS_PER_SAMPLE = 16;
    static constexpr uint8_t CHANNELS = 1;
    static constexpr uint32_t BUFFER_SIZE = 1024;

    Inmp1441();

    Inmp1441(const Inmp1441&) = delete;
    Inmp1441& operator=(const Inmp1441&) = delete;
    Inmp1441(Inmp1441&&) = delete;
    Inmp1441& operator=(Inmp1441&&) = delete;

    ~Inmp1441() override = default;

    void SetDeviceModel(
        IDeviceModel& deviceModel) override;

    void StartRecording();
    void StopRecording();

    [[nodiscard]] bool IsRecording() const;

    void ReadSamples(
        int16_t* buffer,
        size_t length);

    Inmp1441DeviceModel& GetInmp1441DeviceModel();

private:
    Inmp1441DeviceModel* _inmp1441DeviceModel;
    bool _isRecording;
};
