#pragma once

#include "IDomainModel.hpp"

class IDeviceModel;

class DomainModel : public IDomainModel
{
public:
    // Do not make = default;
    DomainModel();

    DomainModel(const DomainModel&) = delete;
    DomainModel& operator=(const DomainModel&) = delete;
    DomainModel(DomainModel&&) = delete;
    DomainModel& operator=(DomainModel&&) = delete;

    // Do not make = default;
    ~DomainModel() override;
};
