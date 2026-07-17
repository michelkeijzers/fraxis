#pragma once
#include "Tm1637Driver.hpp"
#include <cstring> 
#include <cstdint>
#include <array>

class Tm1637Model;

class WindowsTm1637Driver : public Tm1637Driver
{
public:
	WindowsTm1637Driver(Tm1637Model& model);

	void Initialize() override;
	//void Update() override;

	void Write() override;
};
