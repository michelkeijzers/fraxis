#pragma once

#include <string>
#include <span>

class IApplication
{
public:
    enum class EType : uint8_t
    {
        Game,
        Demo,
        Tool,
        Utility,
        Last,
        Menu // Not used for normal iterations
    };

    static constexpr uint8_t NR_OF_TYPES = static_cast<uint8_t>(EType::Last);

    enum class ETag : uint8_t
    {   // Type:           Game Demo Tool Utility
        Arcade,          // x    
        Audio,           // x    x    x    x
        Continuous,      // x
        Diagnostics,     //                x
        Displays,        //      x    x    x
        DistanceSensors, // x    x    x    x
        HardwareTest,    //                x
        Horizontal,      // x    x    x
        Info,            //                x
        Interactive,     // x    x    x    x
        Joysticks,       // x    x    x    x
        Leds,            // x    x    x    x
        LedStrips,       // x    x    x    x
        Microphone,      // x    x    x    x
        Puzzle,          // x
        Racing,          // x
        ServiceTester,   //                \x
        Shooter,         // x
        Speaker,         // x    x    x    x
        SinglePlayer,    // x
        Static,          // x    x    x    x
        TimeBased,       // x    x    x    x
        TurnBased,       // x
        TwoPlayers,      // x
        Vertical,        // x    x    x    x
        Last
    };

    static constexpr uint8_t NR_OF_TAGS = static_cast<uint8_t>(ETag::Last);

    enum class EState : uint8_t
    {
        Idle,
        Running,
        Paused,
    };

    IApplication() = default;

    IApplication(const IApplication&) = delete;
    IApplication& operator=(const IApplication&) = delete;
    IApplication(IApplication&&) = delete;
    IApplication& operator=(IApplication&&) = delete;

    virtual ~IApplication() = default; // NOSONAR VCR001 Function definition not found

    virtual void Start() = 0;
    virtual void Pause() = 0;
    virtual void Resume() = 0;
    virtual void Stop() = 0;
    virtual void Tick() = 0;
};
