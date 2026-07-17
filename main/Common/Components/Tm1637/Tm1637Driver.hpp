#pragma once

#include <cstdint>

class Tm1637Model;

class Tm1637Driver
{
public:
    Tm1637Driver(Tm1637Model& model);

    virtual ~Tm1637Driver() = default;
    
	virtual void Initialize() = 0;
    virtual void Write() = 0;

protected:
	Tm1637Model& _model;
};
