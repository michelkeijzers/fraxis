#pragma once
#include "Tm1637DeviceDriver.hpp"
#include <cstring> 
#include <cstdint>
#include <array>

class Tm1637Model;

class WindowsTm1637DeviceDriver : public Tm1637DeviceDriver
{
public:
	WindowsTm1637DeviceDriver(Tm1637Model& model);

	void Initialize() override;
	//void Update() override;

	void Write() override;
};
