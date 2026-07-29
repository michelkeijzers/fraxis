#include "LedStripsTaskDeviceDriversDelegate.hpp"
#include "Ws28xx/Ws28xxDeviceDriver.hpp"
#include "../L1_Composition/Context/DeviceModelsContext.hpp"
#include "../L1_Composition/Context/Context.hpp"
#include "../L4_DomainModels/LedStrips/LedStrips.hpp"
#include "../L5_DeviceModels/Ws28xx/Ws28xxDeviceModel.hpp"
#include "../L5_DeviceModels/Ws28xx/Ws28xxDeviceModel.hpp"
#include "../L9_Utilities/Time/TimeUtilities.hpp"

LedStripsTaskDeviceDriversDelegate::LedStripsTaskDeviceDriversDelegate(Context& context) 
:   _context(context), _lastWs28xxWriteUs(0)
{
}

LedStripsTaskDeviceDriversDelegate::~LedStripsTaskDeviceDriversDelegate() 
{
}

void LedStripsTaskDeviceDriversDelegate::Initialize() 
{
}

void LedStripsTaskDeviceDriversDelegate::Run()
{
    uint64_t nowUs = 0; // TODO get current time

    uint64_t ledStripsIntervalUs = TimeUtilities::FrequencyToIntervalUs(WS28XX_WRITE_FREQUENCY);
    if (nowUs - _lastWs28xxWriteUs >= ledStripsIntervalUs)
    {
        _context.GetDeviceDrivers().GetWs28xxDeviceDriver().WriteToLedStrip();
        _lastWs28xxWriteUs = nowUs;
    }
}
