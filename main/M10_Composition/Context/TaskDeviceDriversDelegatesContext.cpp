#include "TaskDeviceDriversDelegatesContext.hpp"
#include "../../M60_DeviceDrivers/I2c/I2cTaskDeviceDriversDelegate.hpp"
#include "../../M60_DeviceDrivers/Ws28xx/Ws28xxTaskDeviceDriversDelegate.hpp"
#include "../../M60_DeviceDrivers/PassiveBuzzer/PassiveBuzzerTaskDeviceDriversDelegate.hpp"

// Do not make default.
TaskDeviceDriversDelegatesContext::TaskDeviceDriversDelegatesContext()
{
    // No functionality required.
}

// Do not make default.
TaskDeviceDriversDelegatesContext::~TaskDeviceDriversDelegatesContext() // NOSONAR S3490: no isdefault
{
    // No functionality required.
}

void TaskDeviceDriversDelegatesContext::Set(
    
    std::unique_ptr<M60::I2c::I2cTaskDeviceDriversDelegate> i2cTaskDeviceDriversDelegate,
    std::unique_ptr<M60::PassiveBuzzer::PassiveBuzzerTaskDeviceDriversDelegate>
        passiveBuzzerTaskDeviceDriversDelegate,
    std::unique_ptr<M60::Ws28xx::Ws28xxTaskDeviceDriversDelegate> ws28xxTaskDeviceDriversDelegate)
{
    _i2cTaskDeviceDriversDelegate = std::move(i2cTaskDeviceDriversDelegate);
    _passiveBuzzerTaskDeviceDriversDelegate = std::move(passiveBuzzerTaskDeviceDriversDelegate);
    _ws28xxTaskDeviceDriversDelegate = std::move(ws28xxTaskDeviceDriversDelegate);
}

M60::I2c::I2cTaskDeviceDriversDelegate&
TaskDeviceDriversDelegatesContext::GetI2cTaskDeviceDriversDelegate()
{
    return *_i2cTaskDeviceDriversDelegate;
}

M60::PassiveBuzzer::PassiveBuzzerTaskDeviceDriversDelegate&
TaskDeviceDriversDelegatesContext::GetPassiveBuzzerTaskDeviceDriversDelegate()
{
    return *_passiveBuzzerTaskDeviceDriversDelegate;
}

M60::Ws28xx::Ws28xxTaskDeviceDriversDelegate&
TaskDeviceDriversDelegatesContext::GetWs28xxTaskDeviceDriversDelegate()
{
    return *_ws28xxTaskDeviceDriversDelegate;
}

