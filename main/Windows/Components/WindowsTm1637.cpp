#include "WindowsTm1637.hpp"
#include <cstring>

WindowsTm1637::WindowsTm1637(uint8_t numberOfDigits)
	: Tm1637(numberOfDigits)
{
}

void WindowsTm1637::Initialize()
{
}

//void WindowsTm1637::Update()
//{
//}

void WindowsTm1637::Write()
{
	// Data (_symbols and auxiliary segments) already in base class (Tm1637).
}

void WindowsTm1637::GetStringRepresentation(char* output)
{
	uint8_t outputIndex = 0;
	for (uint8_t index = 0; index < _numberOfDigits; index++)
	{
		output[outputIndex++] = ESymbolToChar(_symbols[index]);
		if (_auxiliarySegments[index])
		{
			if (_numberOfDigits == 4)
			{
				output[outputIndex++] = ':';
			}
			else
			{
				output[outputIndex++] = '.';
			}
		}
	}
    output[outputIndex] = '\0';
}