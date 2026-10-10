#pragma once

#include "../../DomainModel.hpp"
#include "../../../M30_Messages/Types.hpp"
#include <cstdint>
#include <vector>

class DacDeviceModel;

class Max53987a : public DomainModel
{
public:
    static constexpr uint32_t SAMPLE_RATE = 16000;
    static constexpr uint16_t BITS_PER_SAMPLE = 16;
    static constexpr uint8_t CHANNELS = 1;
    static constexpr uint32_t BUFFER_SIZE = 1024;

    Max53987a();
    ~Max53987a() = default;

    void SetDeviceModel(
        IDeviceModel& deviceModel) override;

    void WriteSamples(
        const int16_t* buffer,
        size_t length);

    DacDeviceModel& GetDacDeviceModel();

private:
    DacDeviceModel* _dacDeviceModel;
};
