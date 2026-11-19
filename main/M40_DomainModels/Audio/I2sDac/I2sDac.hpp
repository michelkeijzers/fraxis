#pragma once

#include "../../DomainModel.hpp"
#include "../../../M30_Messages/Types.hpp"
#include <cstdint>
#include <vector>

class Max53987aDeviceModel;

class I2sDac : public DomainModel
{
public:
    static constexpr uint32_t SAMPLE_RATE = 16000;
    
    static constexpr uint16_t BITS_PER_SAMPLE = 16;
    
    static constexpr uint8_t CHANNELS = 1;
    
    static constexpr uint32_t BUFFER_SIZE = 1024;

    I2sDac();

    I2sDac(
        const I2sDac&) = delete;

    I2sDac& operator=(
        const I2sDac&) = delete;

    I2sDac(
        I2sDac&&) = delete;

    I2sDac& operator=(
        I2sDac&&) = delete;

    ~I2sDac() override = default;

    void SetDeviceModel(
        IDeviceModel& deviceModel) override;

    void WriteSamples(
        const int16_t* buffer,
        size_t length);

    Max53987aDeviceModel& GetMax53987aDeviceModel();

private:
    Max53987aDeviceModel* _max53987aDeviceModel;
};
