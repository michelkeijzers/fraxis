#include "TaskDeviceDriversDelegatesContext.hpp"
#include "../../M60_DeviceDrivers/I2c/I2cTaskDeviceDriversDelegate.hpp"
#include "../../M60_DeviceDrivers/I2s/I2sTaskDeviceDriversDelegate.hpp"
#include "../../M60_DeviceDrivers/PassiveBuzzer/PassiveBuzzerTaskDeviceDriversDelegate.hpp"
#include "../../M60_DeviceDrivers/SevenSegmentsDisplays/SevenSegmentsDisplaysTaskDeviceDriversDelegate.hpp"
#include "../../M60_DeviceDrivers/Spi/SpiTaskDeviceDriversDelegate.hpp"
#include "../../M60_DeviceDrivers/Ws28xx/Ws28xxTaskDeviceDriversDelegate.hpp"

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
    std::unique_ptr<M60::I2s::I2sTaskDeviceDriversDelegate> i2sTaskDeviceDriversDelegate,
    std::unique_ptr<M60::PassiveBuzzer::PassiveBuzzerTaskDeviceDriversDelegate>
        passiveBuzzerTaskDeviceDriversDelegate,
    std::unique_ptr<M60::SevenSegmentsDisplays::SevenSegmentsDisplaysTaskDeviceDriversDelegate> 
        sevenSegmentsDisplaysTaskDeviceDriversDelegate,
    std::unique_ptr<M60::Spi::SpiTaskDeviceDriversDelegate> spiTaskDeviceDriversDelegate,
    std::unique_ptr<M60::Ws28xx::Ws28xxTaskDeviceDriversDelegate> ws28xxTaskDeviceDriversDelegate)
{
    _i2cTaskDeviceDriversDelegate = std::move(i2cTaskDeviceDriversDelegate);
    _i2sTaskDeviceDriversDelegate = std::move(i2sTaskDeviceDriversDelegate);
    _passiveBuzzerTaskDeviceDriversDelegate = std::move(passiveBuzzerTaskDeviceDriversDelegate);
    _sevenSegmentsDisplaysTaskDeviceDriversDelegate = std::move(
        sevenSegmentsDisplaysTaskDeviceDriversDelegate);
    _spiTaskDeviceDriversDelegate = std::move(spiTaskDeviceDriversDelegate);
    _ws28xxTaskDeviceDriversDelegate = std::move(ws28xxTaskDeviceDriversDelegate);
}

M60::I2c::I2cTaskDeviceDriversDelegate&
TaskDeviceDriversDelegatesContext::GetI2cTaskDeviceDriversDelegate()
{
    return *_i2cTaskDeviceDriversDelegate;
}

M60::I2s::I2sTaskDeviceDriversDelegate&
TaskDeviceDriversDelegatesContext::GetI2sTaskDeviceDriversDelegate()
{
    return *_i2sTaskDeviceDriversDelegate;
}

M60::PassiveBuzzer::PassiveBuzzerTaskDeviceDriversDelegate&
TaskDeviceDriversDelegatesContext::GetPassiveBuzzerTaskDeviceDriversDelegate()
{
    return *_passiveBuzzerTaskDeviceDriversDelegate;
}

M60::SevenSegmentsDisplays::SevenSegmentsDisplaysTaskDeviceDriversDelegate&
TaskDeviceDriversDelegatesContext::GetSevenSegmentsDisplaysTaskDeviceDriversDelegate()
{
    return *_sevenSegmentsDisplaysTaskDeviceDriversDelegate;
}

M60::Spi::SpiTaskDeviceDriversDelegate&
TaskDeviceDriversDelegatesContext::GetSpiTaskDeviceDriversDelegate()
{
    return *_spiTaskDeviceDriversDelegate;
}

M60::Ws28xx::Ws28xxTaskDeviceDriversDelegate&
TaskDeviceDriversDelegatesContext::GetWs28xxTaskDeviceDriversDelegate()
{
    return *_ws28xxTaskDeviceDriversDelegate;
}
