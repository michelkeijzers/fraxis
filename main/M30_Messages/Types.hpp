#pragma once

class Types
{
public:
    enum class ETaskId
    {
        /// @brief Use for non tasks, such as initialization/boot.
        System,
        /// @brief Only use for Windows
        Windows,
        ApplicationsTask,
        I2cTask,
        SpiTask,
        LedStripsTask,
        DiagnosticsTask
    };

    enum class ELogLevel
    {
        Debug = 1 << 0,
        Info = 1 << 1,
        Warning = 1 << 2,
        Error = 1 << 3,
        Critical = 1 << 4
    };

    enum class ELedId
    {
        Player1 = 0,
        Player2 = 1,
        PlayPause = 2,
        Select = 3,
        Setup = 4
    };

    enum class EJoystickId
    {
        Player1 = 0,
        Player2 = 1
    };

    enum class EJoystickDirection
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

    enum class ETm1637Id
    {
        CentralPanel = 0,
        Player1 = 1,
        Player2 = 2
    };

    /// @brief Orientation of the led strips.
    /// @details The default is Horizontal.
    enum class ELedStripsOrientation
    {
        Horizontal = 0,
        Vertical = 1
    };
};
