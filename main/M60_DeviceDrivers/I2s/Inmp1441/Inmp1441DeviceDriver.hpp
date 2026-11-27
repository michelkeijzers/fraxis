#pragma once

#include "IInmp1441DeviceDriver.hpp"
#include "../I2sDeviceDriver.hpp"
#include <cstdint>

namespace M90::Assert
{
    class IAssert;
}

namespace M90::String
{
    class IStringUtilities;
}

namespace M60::I2s
{
    class Inmp1441DeviceDriver : public I2sDeviceDriver, public IInmp1441DeviceDriver
    {
    public:
        // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
        Inmp1441DeviceDriver(
           M90::Assert::IAssert& assert,
           M90::String::IStringUtilities& stringUtilities);

        Inmp1441DeviceDriver(
            const Inmp1441DeviceDriver&) = delete;
        
        Inmp1441DeviceDriver& operator=(
            const Inmp1441DeviceDriver&) = delete;
        
        Inmp1441DeviceDriver(
            Inmp1441DeviceDriver&&) = delete;
        
        Inmp1441DeviceDriver& operator=(
            Inmp1441DeviceDriver&&) = delete;

        // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
        ~Inmp1441DeviceDriver() override;

        void StartRecording() override;
        
        void StopRecording() override;

        size_t ReadSamples(
            int16_t* buffer,
            size_t length) override;

        void SetInmp1441DeviceModel(
            M50::I2s::IInmp1441DeviceModel& inmp1441DeviceModel) override;

        M50::I2s::IInmp1441DeviceModel& GetInmp1441DeviceModel() override;

    private:
        M50::I2s::IInmp1441DeviceModel* _inmp1441DeviceModel;

        bool _isRecording;
    };
}