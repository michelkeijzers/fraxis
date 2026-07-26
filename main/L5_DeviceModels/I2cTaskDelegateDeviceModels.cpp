#include "I2cTaskDelegateDeviceModels.hpp"
#include "Lcd2004/Lcd2004Model.hpp"
#include "../L1_Composition/Context/DeviceModelsContext.hpp"
#include "../L1_Composition/Context/Context.hpp"

I2cTaskDelegateDeviceModels::I2cTaskDelegateDeviceModels(Context& context) 
: _context(context)
{
}

I2cTaskDelegateDeviceModels::~I2cTaskDelegateDeviceModels() 
{
}

void I2cTaskDelegateDeviceModels::Run()
{
    DeviceModelsContext& deviceModelsContext = _context.GetDeviceModels();
    Lcd2004Model& lcd2004Model = deviceModelsContext.GetLcd2004Model();

    if (lcd2004Model.IsDirty())
    {
        lcd2004Model.WriteToDriver();   
    }
}
