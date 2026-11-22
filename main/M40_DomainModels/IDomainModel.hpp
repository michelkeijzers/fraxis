#pragma once

class IDeviceModel;

namespace M90::Assert
{
    class IAssert;
}

namespace M90::Log
{
    class ILog;
}

class IDomainModel
{
public:
    virtual ~IDomainModel() = default;

    virtual void SetDeviceModel(
        IDeviceModel& deviceModel) = 0;

    virtual M90::Assert::IAssert& GetAssert() = 0;

    virtual M90::Log::ILog& GetLog() = 0;
};
