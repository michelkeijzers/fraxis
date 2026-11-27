#pragma once

#include "IDomainModel.hpp"

namespace M50
{
    class IDeviceModel;
}

class DomainModel : public IDomainModel
{
public:
    // Do not make = default;
    DomainModel(
        M50::IDeviceModel& deviceModel,
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log);

    DomainModel(
        const DomainModel&) = delete;

    DomainModel& operator=(
        const DomainModel&) = delete;

    DomainModel(
        DomainModel&&) = delete;

    DomainModel& operator=(
        DomainModel&&) = delete;

    // Do not make = default;
    ~DomainModel() override;

    M90::Assert::IAssert& GetAssert() override;
        
    M90::Log::ILog& GetLog() override;

    M50::IDeviceModel& GetDeviceModel() override;

private:
    M50::IDeviceModel& _deviceModel;

    M90::Assert::IAssert& _assert;

    M90::Log::ILog& _log;

};
