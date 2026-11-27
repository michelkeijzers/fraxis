#pragma once

#include "IMax53987aDeviceDriver.hpp"
#include "../I2sDeviceDriver.hpp"
#include <cstdint>

namespace M60::I2s
{
    class Max53987aDeviceDriver : public I2sDeviceDriver, public IMax53987aDeviceDriver
    {
    public:
        // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
        Max53987aDeviceDriver(
            M90::Assert::IAssert& assert,
            M90::String::IStringUtilities& stringUtilities);
        
        Max53987aDeviceDriver(
            const Max53987aDeviceDriver&) = delete;
        
        Max53987aDeviceDriver& operator=(
            const Max53987aDeviceDriver&) = delete;
        
        Max53987aDeviceDriver(
            Max53987aDeviceDriver&&) = delete;
        
        Max53987aDeviceDriver& operator=(
            Max53987aDeviceDriver&&) = delete;

        // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
        ~Max53987aDeviceDriver() override;

        size_t WriteSamples(
            const int16_t* buffer,
            size_t length);

        void SetMax53987aDeviceModel(
            M50::I2s::IMax53987aDeviceModel& max53987aDeviceModel) override;

        M50::I2s::IMax53987aDeviceModel& GetMax53987aDeviceModel() override;

    private:
        M50::I2s::IMax53987aDeviceModel* _max53987aDeviceModel;
    };
}