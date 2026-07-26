#include "I2cTaskDeviceDriversDelegate.hpp"
#include "../L5_DeviceModels/Lcd2004/Lcd2004Model.hpp"
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
    Lcd2004Model& lcd2004Model = deviceModelsContext.GetLcd2004Model();

    if (lcd2004Model.IsDirty())
    {
        //TODO
    }
}
