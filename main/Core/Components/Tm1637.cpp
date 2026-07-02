#include "Tm1637.hpp"
#include <cstdio>
#include <cstring>

Tm1637::Tm1637(uint8_t nrOfDigits) 
: _numberOfDigits(nrOfDigits) , _brightness(0), _symbols { ESymbol::Empty }, _auxiliarySegments { false }
{
}

void Tm1637::SetBrightness(uint8_t brightness)
{
    _brightness = brightness & 0x07; // Limit to 0-7
}


void Tm1637::ClearData()
{
    for (uint8_t i = 0; i < _numberOfDigits; i++)
    {
        _symbols[i] = ESymbol::Empty;
        _auxiliarySegments[i] = false;
    }

}
void Tm1637::Clear()
{
    ClearData();
    Write();
}

void Tm1637::SetTime(uint8_t first, uint8_t second)
{
    first = first % 60;
    second = second % 60;

    ClearData();

    _symbols[0] = ESymbol((uint8_t)Digit0 + (first / 10));
    _symbols[1] = ESymbol((uint8_t)Digit0 + (first % 10));
    _auxiliarySegments[1] = true;
    _symbols[2] = ESymbol((uint8_t)Digit0 + (second / 10));
    _symbols[3] = ESymbol((uint8_t)Digit0 + (second % 10));
    RemoveLeadingZeros(4);
    Write();
}

void Tm1637::Set4DigitsValue(uint32_t value)
{
    value = value % 10000;
    ClearData();

    _symbols[0] = ESymbol((uint8_t)Digit0 + ((value / 1000) % 10));
    _symbols[1] = ESymbol((uint8_t)Digit0 + ((value / 100) % 10));
    _symbols[2] = ESymbol((uint8_t)Digit0 + ((value / 10) % 10));
    _symbols[3] = ESymbol((uint8_t)Digit0 + (value % 10));

    RemoveLeadingZeros(4);
    Write();
}

void Tm1637::SetValue(uint32_t value)
{
    value = value % 1000000;
    ClearData();

    _symbols[0] = ESymbol((uint8_t)Digit0 + ((value / 100000) % 10));
    _symbols[1] = ESymbol((uint8_t)Digit0 + ((value / 10000) % 10));
    _symbols[2] = ESymbol((uint8_t)Digit0 + ((value / 1000) % 10));
    _symbols[3] = ESymbol((uint8_t)Digit0 + ((value / 100) % 10));
    _symbols[4] = ESymbol((uint8_t)Digit0 + ((value / 10) % 10));
    _symbols[5] = ESymbol((uint8_t)Digit0 + (value % 10));

    RemoveLeadingZeros(6);
    Write();
}


/// @brief 
/// Removes leading 0's.
/// @param length 
void Tm1637::RemoveLeadingZeros(uint8_t length)
{
    for (uint8_t i = 0; i < length - 1; i++)
    {
        if (_auxiliarySegments[i])
        {
            break;
        }

        if (_symbols[i] == ESymbol::Digit0)
        {
            _symbols[i] = ESymbol::Empty;
        }
        else
        {
            break;
        }
    }
}

uint8_t Tm1637::EncodeDigitNr(uint8_t index)
{
    ESymbol symbol = _symbols[index];
    uint8_t value = 0;
    switch (symbol)
    {
        case ESymbol::Digit0: value = 0x40; break;
        case ESymbol::Digit1: value = 0x79; break;
        case ESymbol::Digit2: value = 0x24; break;
        case ESymbol::Digit3: value = 0x30; break;
        case ESymbol::Digit4: value = 0x19; break;
        case ESymbol::Digit5: value = 0x12; break;
        case ESymbol::Digit6: value = 0x02; break;
        case ESymbol::Digit7: value = 0x78; break;
        case ESymbol::Digit8: value = 0x00; break;
        case ESymbol::Digit9: value = 0x10; break;
        case ESymbol::Empty: value = 0x00; break;
        default: value = 0; break;
    }

    if (_auxiliarySegments[index]) 
    {
        value |= 0x80;
    }
    return value;
}

/* static */char Tm1637::ESymbolToChar(ESymbol symbol)
{
    switch (symbol)
    {
    case ESymbol::Empty: return ' '; break;
    case ESymbol::Digit0: return '0'; break;
    case ESymbol::Digit1: return '1'; break;
    case ESymbol::Digit2: return '2'; break;
    case ESymbol::Digit3: return '3'; break;
    case ESymbol::Digit4: return '4'; break;
    case ESymbol::Digit5: return '5'; break;
    case ESymbol::Digit6: return '6'; break;
    case ESymbol::Digit7: return '7'; break;
    case ESymbol::Digit8: return '8'; break;
    case ESymbol::Digit9: return '9'; break;
    default: return '?'; break;
    }
}
