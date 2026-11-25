#include "Ws28xxTaskDeviceDriversDelegate.hpp"
#include "Ws28xxDeviceDriver.hpp"

namespace M60::Ws28xx
{
    Ws28xxTaskDeviceDriversDelegate::Ws28xxTaskDeviceDriversDelegate(
        M60::Ws28xx::IWs28xxDeviceDriver& ws28xxDeviceDriver,
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log)
    :
        TaskDeviceDriversDelegate(assert, log),
        _ws28xxDeviceDriver(ws28xxDeviceDriver)
    {
        // No actions required
    }


    void Ws28xxTaskDeviceDriversDelegate::Initialize() // NOSONAR: no const because of virtual 
    {
        // No actions necessary.
    }

    /// @brief: Runs the delegate.
    /// @details: In normal tasks there is a fixed frequency. However, for led strips the message 
    ///FrameReady will be used to decide to update to the led strips.
    void Ws28xxTaskDeviceDriversDelegate::Run()
    {
        {
            _ws28xxDeviceDriver.WriteToLedStrip();
        }
    }
}
