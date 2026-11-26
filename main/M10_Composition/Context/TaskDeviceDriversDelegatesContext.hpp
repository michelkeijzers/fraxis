#pragma once

#include <memory>

namespace M60::I2c
{
    class I2cTaskDeviceDriversDelegate;
}

namespace M60::PassiveBuzzer
{
    class PassiveBuzzerTaskDeviceDriversDelegate;
}

namespace M60::Ws28xx
{
    class Ws28xxTaskDeviceDriversDelegate;
}

class TaskDeviceDriversDelegatesContext
{
public:
    /// @brief Do NOT make = default, this causes issues relating to Context class.
    TaskDeviceDriversDelegatesContext();

    TaskDeviceDriversDelegatesContext(
        const TaskDeviceDriversDelegatesContext&) = delete;

    TaskDeviceDriversDelegatesContext& operator=(
        const TaskDeviceDriversDelegatesContext&) = delete;

    TaskDeviceDriversDelegatesContext(
        TaskDeviceDriversDelegatesContext&&) = delete;

    TaskDeviceDriversDelegatesContext& operator=(
        TaskDeviceDriversDelegatesContext&&) = delete;

    /// @brief Do NOT make = default, this causes issues relating to Context class.
    ~TaskDeviceDriversDelegatesContext();

    void Set(
        std::unique_ptr<M60::I2c::I2cTaskDeviceDriversDelegate> i2cTaskDeviceDriversDelegate,
        std::unique_ptr<M60::PassiveBuzzer::PassiveBuzzerTaskDeviceDriversDelegate>
            passiveBuzzerTaskeviceDriversDelegate,
        std::unique_ptr<M60::Ws28xx::Ws28xxTaskDeviceDriversDelegate>
            ws28xxTaskDeviceDriversDelegate);

    M60::I2c::I2cTaskDeviceDriversDelegate& GetI2cTaskDeviceDriversDelegate();

    M60::PassiveBuzzer::PassiveBuzzerTaskDeviceDriversDelegate&
        GetPassiveBuzzerTaskDeviceDriversDelegate();

    M60::Ws28xx::Ws28xxTaskDeviceDriversDelegate& GetWs28xxTaskDeviceDriversDelegate();

private:
    std::unique_ptr<M60::I2c::I2cTaskDeviceDriversDelegate> _i2cTaskDeviceDriversDelegate;

    std::unique_ptr<M60::PassiveBuzzer::PassiveBuzzerTaskDeviceDriversDelegate>
        _passiveBuzzerTaskDeviceDriversDelegate;

    std::unique_ptr<M60::Ws28xx::Ws28xxTaskDeviceDriversDelegate>
        _ws28xxTaskDeviceDriversDelegate;
};
