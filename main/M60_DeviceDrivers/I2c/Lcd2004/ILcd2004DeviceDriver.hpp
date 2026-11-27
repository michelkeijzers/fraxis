#pragma once

#include <cstdint>

namespace M81::RtosTask
{
    class IRtosTask;
}

namespace M50::I2c
{
    class ILcd2004DeviceModel;
}

namespace M60::I2c
{
    class I2cDeviceDriver;

    static constexpr uint8_t LCD2004_NUMBER_OF_CUSTOM_CHARACTERS = 8;
    static constexpr uint8_t LCD2004_NUMBER_OF_PREDEFINED_CHARACTERS = 2;
    static constexpr uint8_t LCD2004_CUSTOM_CHARACTER_DATA_LENGTH = 8;

    class ILcd2004DeviceDriver
    {
    public:
        enum class EPredefinedCharacters : uint8_t
        {
            TriangleUp,
            TriangleDown
        };

        virtual ~ILcd2004DeviceDriver() = default;

        virtual void SetLcd2004DeviceModel(
            M50::I2c::ILcd2004DeviceModel& lcd2004DeviceModel) = 0;

        virtual M50::I2c::ILcd2004DeviceModel& GetLcd2004DeviceModel() = 0;

        virtual M81::RtosTask::IRtosTask& GetRtosTask() = 0;
        
        virtual void SetRtosTask(
            M81::RtosTask::IRtosTask& rtosTask) = 0;
        
        virtual void Update() = 0;
    };
}
