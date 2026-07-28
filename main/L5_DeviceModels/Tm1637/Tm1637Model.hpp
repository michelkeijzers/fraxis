#pragma once

#include "../DeviceModel.hpp"
#include "../../L9_Utilities/Dirty/IDirty.hpp"

class Tm1637Model : public DeviceModel, public IDirty
{
public:
    Tm1637Model();
    ~Tm1637Model();

    void Initialize() override;
};
