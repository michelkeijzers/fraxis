#pragma once

#include "../DeviceModel.hpp"
#include "../../L9_Utilities/Dirty/IDirty.hpp"

class Tm1637DeviceModel : public DeviceModel, public IDirty
{
public:
    Tm1637DeviceModel();
    ~Tm1637DeviceModel();

    void Initialize() override;
};
