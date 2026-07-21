#pragma once

#include "../ComponentModel.hpp"
#include <cstdint>

class Tm1637Model : public ComponentModel
{
public:
	 enum ESymbol
	 {
		 Empty,
		 Digit0,
		 Digit1,
		 Digit2,
		 Digit3,
		 Digit4,
		 Digit5,
		 Digit6,
		 Digit7,
		 Digit8,
		 Digit9
	};

    Tm1637Model(uint8_t nrOfDigits);

    virtual ~Tm1637Model() = default;
    
    void SetBrightness(uint8_t brightness);

    void Clear();
    void SetTime(uint8_t first, uint8_t second);
    void Set4DigitsValue(uint32_t value);
    void SetValue(uint32_t value);

	static char ESymbolToChar(ESymbol symbol);
	ESymbol* GetSymbols() { return _symbols; }

	uint8_t EncodeDigitNr(uint8_t index);
	uint8_t GetNumberOfDigits() { return _numberOfDigits; }
	uint8_t GetBrightness() { return _brightness; }
    
    void GetStringRepresentation(char* output);

protected:
    uint8_t _numberOfDigits;   // 4 or 6

    uint8_t _brightness;       // 0-7

	ESymbol _symbols[6]; // Filled up until _numberOfDigits
 	bool _auxiliarySegments[6]; // Filled up until _numberOfDigits

private:
	void ClearData();
    void RemoveLeadingZeros(uint8_t length);
};