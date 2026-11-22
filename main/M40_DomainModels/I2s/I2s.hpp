#pragma once

#include "../DomainModel.hpp"
#include "../../M30_Messages/Types.hpp"
#include <cstdint>
#include <vector>

class I2sDeviceModel;

class I2s : public DomainModel
{
public:
    static constexpr uint32_t SAMPLE_RATE = 16000;
    
    static constexpr uint16_t BITS_PER_SAMPLE = 16;
    
    static constexpr uint8_t CHANNELS = 1;
    
    static constexpr uint32_t BUFFER_SIZE = 1024;

    I2s(
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log);

    ~I2s() = default;

    void SetDeviceModel(
        IDeviceModel& deviceModel) override;

    I2sDeviceModel& GetI2sDeviceModel();

private:
    I2sDeviceModel* _i2sDeviceModel;
};
