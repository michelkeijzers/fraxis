#include "DomainModel.hpp"

DomainModel::DomainModel(
    M50::IDeviceModel& deviceModel,
    M90::Assert::IAssert& assert,
    M90::Log::ILog& log)
:
    _deviceModel(deviceModel),
    _assert(assert),
    _log(log)
{
    // No functionality required.
}

DomainModel::~DomainModel() // NOSONAR S3490 Do not make = default;
{
    // No functionality required.
}

M50::IDeviceModel& DomainModel::GetDeviceModel()
{
    return _deviceModel;
}

M90::Assert::IAssert& DomainModel::GetAssert()
{
    return _assert;
}

M90::Log::ILog& DomainModel::GetLog()
{
    return _log;
}
