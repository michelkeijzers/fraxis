#include "I2s.hpp"
#include "../../M50_DeviceModels/I2s/I2sDeviceModel.hpp"

I2s::I2s(
    M90::Assert::IAssert& assert,
    M90::Log::ILog& log)
: 
    DomainModel(assert, log),
    _i2sDeviceModel(nullptr)
{
    //  No functionality required.
}

void I2s::SetDeviceModel(
    M50::IDeviceModel& deviceModel)
{
    _i2sDeviceModel = static_cast<M50::I2s::I2sDeviceModel*>(&deviceModel);
}

M50::I2s::I2sDeviceModel& I2s::GetI2sDeviceModel()
{
    return *_i2sDeviceModel;
}
