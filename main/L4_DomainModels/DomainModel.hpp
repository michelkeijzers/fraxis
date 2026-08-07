#pragma once

#include "IDomainModel.hpp"

class IDeviceModel;

class DomainModel : public IDomainModel
{
public:
    DomainModel();
    virtual ~DomainModel() = default;
};
