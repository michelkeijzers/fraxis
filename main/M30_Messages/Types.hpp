#pragma once

#include <cstdint>

class Types
{
public:
    enum class ETaskId : uint8_t
    {
        /// @brief Use for non tasks, such as initialization/boot.
        System,
        /// @brief Only use for Windows
        Windows,
        ApplicationsTask,
        I2cTask,
        SpiTask,
        LedStripsTask,
        DiagnosticsTask,
        AudioTask
    };

    enum class ELogLevel : uint8_t
    {
        Debug = 1 << 0,
        Info = 1 << 1,
        Warning = 1 << 2,
        Error = 1 << 3,
        Critical = 1 << 4
    };

    enum class ELedId : uint8_t
    {
        Player1 = 0,
        Player2 = 1,
        PlayPause = 2,
        Select = 3,
        Setup = 4
    };

    enum class EJoystickId : uint8_t
    {
        Player1 = 0,
        Player2 = 1
    };

    enum class EJoystickDirection : uint8_t
    {
        Centered = 0,
        Up = 1, 
        UpRight = 2,
        Right = 3,
        DownRight = 4,
        Down = 5,
        DownLeft = 6,
        Left = 7,
        UpLeft = 8
    };

    enum class ETm1637Id : uint8_t
    {
        CentralPanel = 0,
        Player1 = 1,
        Player2 = 2
    };

    /// @brief Orientation of the led strips.
    /// @details The default is Horizontal.
    enum class ELedStripsOrientation : uint8_t
    {
        Horizontal = 0,
        Vertical = 1
    };

    enum class EAudioDeviceId : uint8_t
    {
        Microphone = 0,
        Dac = 1
    };

    enum class EBuzzerId : uint8_t
    {
        SystemBuzzer = 0
    };

    enum class EAudioSampleId : uint8_t
    {
        None = 0,
        MaxSamples = 50
    };

    enum class EAudioChannel : uint8_t
    {
        Left = 0,
        Right = 1
    };
};
