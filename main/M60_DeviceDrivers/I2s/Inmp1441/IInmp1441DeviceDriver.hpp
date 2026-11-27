#pragma once

#include <cstdint>
// Do not remove cstddef, needed for size_t in ESP build.
#include <cstddef>

namespace M50::I2s
{
    class IInmp1441DeviceModel;
}

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
    class IInmp1441DeviceDriver
    {
    public:
        virtual ~IInmp1441DeviceDriver() = default;

        virtual void SetInmp1441DeviceModel(
            M50::I2s::IInmp1441DeviceModel& inmp1441DeviceModel) = 0;

        virtual M50::I2s::IInmp1441DeviceModel& GetInmp1441DeviceModel() = 0;

        virtual void StartRecording() = 0;
        
        virtual void StopRecording() = 0;

        virtual size_t ReadSamples(
            int16_t* buffer,
            size_t length) = 0;
    };
}