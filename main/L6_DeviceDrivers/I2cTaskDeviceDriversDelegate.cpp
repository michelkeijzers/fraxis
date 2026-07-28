#include "I2cTaskDeviceDriversDelegate.hpp"
#include "../L5_DeviceModels/Lcd2004/Lcd2004DeviceModel.hpp"
#include "../L1_Composition/Context/DeviceModelsContext.hpp"
#include "../L1_Composition/Context/Context.hpp"

I2cTaskDeviceDriversDelegate::I2cTaskDeviceDriversDelegate(Context& context) 
: _context(context)
{
}

I2cTaskDeviceDriversDelegate::~I2cTaskDeviceDriversDelegate() 
{
}

void I2cTaskDeviceDriversDelegate::Run()
{
    DeviceModelsContext& deviceModelsContext = _context.GetDeviceModels();

    Lcd2004DeviceModel& lcd2004DeviceModel = deviceModelsContext.GetLcd2004DeviceModel();

    if (lcd2004DeviceModel.IsDirty())
    {
        _context.GetDeviceDrivers().GetLcd2004DeviceDriver().SendToDisplay();
    }
}
