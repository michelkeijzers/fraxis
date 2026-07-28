#pragma once

#include "../DeviceModel.hpp"
#include "../../L9_Utilities/Dirty/IDirty.hpp"

class Ws28xxModel : public DeviceModel, public IDirty
{
public:
    Ws28xxModel();
    ~Ws28xxModel();

    void Initialize() override;
};
