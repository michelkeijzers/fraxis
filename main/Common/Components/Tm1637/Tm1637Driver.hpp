#pragma once

#include <cstdint>

class Tm1637Model;

class Tm1637DeviceDriver
{
public:
    Tm1637DeviceDriver(Tm1637Model& model);

    virtual ~Tm1637DeviceDriver() = default;
    
	virtual void Initialize() = 0;
    virtual void Write() = 0;

protected:
	Tm1637Model& _model;
};
