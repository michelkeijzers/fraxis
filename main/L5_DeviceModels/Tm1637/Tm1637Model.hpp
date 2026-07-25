#pragma once

#include "../DeviceModel.hpp"

class Tm1637Model : public DeviceModel
{
public:
    Tm1637Model();
    ~Tm1637Model();

    void Initialize() override;
};
