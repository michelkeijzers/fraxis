#pragma once

#include <cstdint>

class Tm1637DeviceModel;

class Tm1637DeviceDriver
{
public:
    Tm1637DeviceDriver(Tm1637DeviceModel& model);

    virtual ~Tm1637DeviceDriver() = default;
    
	virtual void Initialize() = 0;
    virtual void Write() = 0;

protected:
	Tm1637DeviceModel& _model;
};
