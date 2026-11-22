#pragma once

#include "IDomainModel.hpp"

class IDeviceModel;

class DomainModel : public IDomainModel
{
public:
    // Do not make = default;
    DomainModel(
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

private:
    M90::Assert::IAssert& _assert;

    M90::Log::ILog& _log;

};
