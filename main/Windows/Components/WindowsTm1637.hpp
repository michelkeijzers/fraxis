#pragma once
#include "../../Core/Components/Tm1637.hpp"
#include <cstring> 
#include <cstdint>
#include <array>

class WindowsTm1637 : public Tm1637
{
public:
	WindowsTm1637(uint8_t numberOfDigits);

	void Initialize() override;
	//void Update() override;

	void Write() override;

	void GetStringRepresentation(char* output);
};