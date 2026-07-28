#include "Tm1637.hpp"
#include "../../../../L5_DeviceModels/Tm1637/Tm1637DeviceModel.hpp"

Tm1637::Tm1637()
{
}

void Tm1637::SetDeviceModel(IDeviceModel& deviceModel)
{
    _tm1637DeviceModel = static_cast<Tm1637DeviceModel*>(&deviceModel);
}