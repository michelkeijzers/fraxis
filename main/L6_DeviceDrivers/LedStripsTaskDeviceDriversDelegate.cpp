#include "LedStripsTaskDeviceDriversDelegate.hpp"
#include "Ws28xx/Ws28xxDeviceDriver.hpp"
#include "../L1_Composition/Context/DeviceModelsContext.hpp"
#include "../L1_Composition/Context/Context.hpp"
#include "../L4_DomainModels/LedStrips/LedStrips.hpp"
#include "../L5_DeviceModels/Ws28xx/Ws28xxDeviceModel.hpp"
#include "../L5_DeviceModels/Ws28xx/Ws28xxDeviceModel.hpp"
#include "../L9_Utilities/Time/TimeUtilities.hpp"

LedStripsTaskDeviceDriversDelegate::LedStripsTaskDeviceDriversDelegate(
    Context& context) 
:   _context(context)
{
}

void LedStripsTaskDeviceDriversDelegate::Initialize() // NOSONAR: no const because of virtual 
{
    // No actions necessary.
}

/// @brief: Runs the delegate.
/// @details: In normal tasks there is a fixed frequency. However, for led strips the message FrameReady will be used to decide
/// to update to the led strips.
void LedStripsTaskDeviceDriversDelegate::Run()
{
    {
        _context.GetDeviceDrivers().GetWs28xxDeviceDriver().WriteToLedStrip();
    }
}
