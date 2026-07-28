#pragma once

#include "../DeviceModel.hpp"
#include "../../L9_Utilities/Dirty/IDirty.hpp"

class Ws28xxDeviceModel : public DeviceModel, public IDirty
{
public:
    Ws28xxDeviceModel();
    ~Ws28xxDeviceModel();

    void Initialize() override;
};
