#pragma once

namespace M50
{
    class IDeviceModel;
}

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

    virtual M50::IDeviceModel& GetDeviceModel() = 0;

    virtual M90::Assert::IAssert& GetAssert() = 0;

    virtual M90::Log::ILog& GetLog() = 0;
};
