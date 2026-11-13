#include "Ws28xxTaskDeviceDriversDelegate.hpp"
#include "Ws28xxDeviceDriver.hpp"
#include "../../M10_Composition/Context/DeviceModelsContext.hpp"
#include "../../M10_Composition/Context/Context.hpp"
#include "../../M40_DomainModels/LedStrips/LedStrips.hpp"
#include "../../M50_DeviceModels/Ws28xx/Ws28xxDeviceModel.hpp"
#include "../../M90_Utilities/Time/TimeUtilities.hpp"

namespace M60::Ws28xx
{
    Ws28xxTaskDeviceDriversDelegate::Ws28xxTaskDeviceDriversDelegate(
        Context& context)
    :
        _context(context)
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
            _context.GetDeviceDrivers().GetWs28xxDeviceDriver().WriteToLedStrip();
        }
    }
}
