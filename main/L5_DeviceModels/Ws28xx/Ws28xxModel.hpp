#pragma once

#include "../DeviceModel.hpp"

class Ws28xxModel : public DeviceModel
{
public:
    Ws28xxModel();
    ~Ws28xxModel();

    void Initialize() override;
};
