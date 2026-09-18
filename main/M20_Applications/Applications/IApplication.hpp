#pragma once

#include <string>
#include <span>

class IApplication
{
public:
    enum class EType
    {
        Game,
        Demo,
        Tool,
        Utility,
        Last,
        Menu // Not used for normal iterations
    };

    enum class ETag
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

    enum class EState
    {
        Idle,
        Running,
        Paused,
    };

    IApplication();
    virtual ~IApplication();

    virtual std::string_view GetName() const = 0;
    virtual EType GetType() const = 0;
    virtual std::span<const ETag> GetTags() const = 0;

    virtual void Start() = 0;
    virtual void Pause() = 0;
    virtual void Resume() = 0;
    virtual void Stop() = 0;
    virtual void Run() = 0;
};
