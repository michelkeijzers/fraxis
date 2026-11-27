#pragma once

#include "../../DomainModel.hpp"
#include "../../../M30_Messages/Types.hpp"
#include <cstdint>
#include <vector>

namespace M50::I2s
{
    class Inmp1441DeviceModel;
}

class I2sMicrophone : public DomainModel
{
public:
    static constexpr uint32_t SAMPLE_RATE = 16000;
    
    static constexpr uint16_t BITS_PER_SAMPLE = 16;
    
    static constexpr uint8_t CHANNELS = 1;
    
    static constexpr uint32_t BUFFER_SIZE = 1024;

    I2sMicrophone(
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log);

    I2sMicrophone(
        const I2sMicrophone&) = delete;
    
    I2sMicrophone& operator=(
        const I2sMicrophone&) = delete;
    
    I2sMicrophone(
        I2sMicrophone&&) = delete;
    
    I2sMicrophone& operator=(
        I2sMicrophone&&) = delete;

    ~I2sMicrophone() override = default;

    void SetDeviceModel(
        M50::IDeviceModel& deviceModel) override;

    void StartRecording();
    
    void StopRecording();

    [[nodiscard]] bool IsRecording() const;

    void ReadSamples(
        int16_t* buffer,
        size_t length);

    M50::I2s::Inmp1441DeviceModel& GetInmp1441DeviceModel();

private:
    M50::I2s::Inmp1441DeviceModel* _inmp1441DeviceModel;
    
    bool _isRecording;
};
