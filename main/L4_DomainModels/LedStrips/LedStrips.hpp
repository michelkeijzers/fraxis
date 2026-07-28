#pragma once

#include "../DomainModel.hpp"
#include "../../L5_DeviceModels/Ws28xx/Ws28xxDeviceModel.hpp"

class Ws28xxDeviceModel;

class LedStrips : public IDomainModel
{
public:
    LedStrips();
    ~LedStrips();

    void SetDeviceModel(IDeviceModel& deviceModel) override;

private:
    Ws28xxDeviceModel* _ws28xxDeviceModel; 
};
