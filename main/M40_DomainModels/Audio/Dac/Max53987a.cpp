#include "Max53987a.hpp"
#include "../../../M50_DeviceModels/Audio/Dac/DacDeviceModel.hpp"

Max53987a::Max53987a()
: _dacDeviceModel(nullptr)
{
}

void Max53987a::SetDeviceModel(
    IDeviceModel& deviceModel)
{
    _dacDeviceModel = static_cast<DacDeviceModel*>(&deviceModel);
}

void Max53987a::WriteSamples(
    const int16_t* buffer,
    size_t length)
{
}

DacDeviceModel& Max53987a::GetDacDeviceModel()
{
    return *_dacDeviceModel;
}
