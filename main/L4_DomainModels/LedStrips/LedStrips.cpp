#include "LedStrips.hpp"
#include "../../L5_DeviceModels/Mcp23017/Mcp23017DeviceModel.hpp"

LedStrips::LedStrips()
{
}

LedStrips::~LedStrips()
{
}

void LedStrips::SetDeviceModel(IDeviceModel& deviceModel)
{
    _ws28xxDeviceModel = static_cast<Ws28xxDeviceModel*>(&deviceModel);
}
