#include "Tm1637DeviceModel.hpp"
#include "../../L9_Utilities/Assert/Assert.hpp"

Tm1637DeviceModel::Tm1637DeviceModel()
:   DeviceModel(), _segmentsTable {}, 
    _nrOfDigits {}, _characters {}, _dirtyCharacters {}, _auxiliarySegments {}
{
    FillSegmentsTable();
}

Tm1637DeviceModel::~Tm1637DeviceModel()
{
}

uint8_t Tm1637DeviceModel::GetNrOfDigits()
{
    return _nrOfDigits;
}

void Tm1637DeviceModel::SetNrOfDigits(uint8_t nrOfDigits)
{
    Assert::IsTrue((_nrOfDigits == 4) || (_nrOfDigits == 6), "nrOfDigits");
    _nrOfDigits = nrOfDigits;
}

void Tm1637DeviceModel::Initialize()
{
    Assert::IsTrue((_nrOfDigits == 4) || (_nrOfDigits == 6), "nrOfDigits must be set before initialization");
    MarkInitialized();
}

uint8_t Tm1637DeviceModel::GetDigit(uint8_t index)
{
    Assert::IsTrue(IsInitialized());
    Assert::IsTrue(index < _nrOfDigits, "index");

    return uint8_t(_characters[index] - '0');
}

void Tm1637DeviceModel::SetDigit(uint8_t index, uint8_t value)
{
    Assert::IsTrue(IsInitialized());
    Assert::IsTrue(index < _nrOfDigits, "index");
    Assert::IsBetween(value, 0, 10, "value");

    uint8_t newCharacter = '0' + value;
    if (_characters[index] != newCharacter)
    {
        _characters[index] = newCharacter;
        _dirtyCharacters[index] = true;
        MarkDirty();
    }
}

char Tm1637DeviceModel::GetCharacter(uint8_t index)
{
    Assert::IsTrue(IsInitialized());
    Assert::IsTrue(index < _nrOfDigits, "index");

    return _characters[index];
}

void Tm1637DeviceModel::SetCharacter(uint8_t index, char character)
{
    Assert::IsTrue(IsInitialized());
    Assert::IsTrue(index < _nrOfDigits, "index");

    if (_characters[index] != character)
    {
        _characters[index] = character;
        _dirtyCharacters[index] = true;
        MarkDirty();
    }
    _characters[index] = character;
}

bool Tm1637DeviceModel::GetAuxiliarySegment(uint8_t index)
{
    Assert::IsTrue(IsInitialized());
    Assert::IsTrue(index < _nrOfDigits, "index");

    return _auxiliarySegments[index];
}

void Tm1637DeviceModel::SetAuxiliarySegment(uint8_t index, bool state)
{
    Assert::IsTrue(IsInitialized());
    Assert::IsTrue(index < _nrOfDigits, "index");

    if (_auxiliarySegments[index] != state)
    {
        _auxiliarySegments[index] = state;
        _dirtyCharacters[index] = true;
        MarkDirty();
    }
}

/// @brief Get segments value
/// @details Active low.
/// @return 
uint8_t Tm1637DeviceModel::GetSegmentsValue(uint8_t index)
{
    Assert::IsTrue(IsInitialized());
    uint8_t segmentsValue = _segmentsTable[static_cast<uint8_t>(_characters[index])];

    if (_auxiliarySegments[index])
    {
        segmentsValue &= 0x80;
    }
    return segmentsValue;
}

bool Tm1637DeviceModel:: IsCharacterDirty(uint8_t index)
{
    Assert::IsTrue(IsInitialized());
    Assert::IsTrue(index < _nrOfDigits, "index");

    return _dirtyCharacters[index];
}

void Tm1637DeviceModel::ClearDirty()
{
    Assert::IsTrue(IsInitialized());

    for (uint8_t index = 0; index < _nrOfDigits; index++)
    {
        _dirtyCharacters[index] = false;
    }
    DeviceModel::ClearDirty();
}

/// @brief Fill segments table
/// @details Active low.
void Tm1637DeviceModel::FillSegmentsTable()
{
    Assert::IsTrue(IsInitialized());
    _segmentsTable[static_cast<uint8_t>(ESymbol::Degrees)] = 0x0C;   // segments A + B (looks like small circle)

    _segmentsTable[' '] = 0xFF;
    _segmentsTable['-'] = 0x3F;   // segment G only
    _segmentsTable['_'] = 0x70;   // segment D only
    _segmentsTable['='] = 0x31;   // segments G + D
    _segmentsTable['\''] = 0x7B;  // segment B only
    _segmentsTable[','] = 0x7D;   // segment C only
    _segmentsTable['.'] = 0x7F;   // decimal point only
    _segmentsTable[':'] = 0x7F;   // same as '.', but you place it on two digits

    _segmentsTable['0'] = 0x40;
    _segmentsTable['1'] = 0x79;
    _segmentsTable['2'] = 0x24;
    _segmentsTable['3'] = 0x30;
    _segmentsTable['4'] = 0x19;
    _segmentsTable['5'] = 0x12;
    _segmentsTable['6'] = 0x02;
    _segmentsTable['7'] = 0x78;
    _segmentsTable['8'] = 0x00;
    _segmentsTable['9'] = 0x10;

    _segmentsTable['A'] = 0x08;
    _segmentsTable['B'] = 0x03;
    _segmentsTable['C'] = 0x46;
    _segmentsTable['D'] = 0x21;
    _segmentsTable['E'] = 0x06;
    _segmentsTable['F'] = 0x0E;
    _segmentsTable['G'] = 0x02;   // same as '6'
    _segmentsTable['H'] = 0x0B;
    _segmentsTable['I'] = 0x4F;
    _segmentsTable['J'] = 0x71;
    _segmentsTable['L'] = 0x47;
    _segmentsTable['N'] = 0x0B;   // approximation (same as H)
    _segmentsTable['O'] = 0x40;   // same as '0'
    _segmentsTable['P'] = 0x0C;
    _segmentsTable['Q'] = 0x18;   // approximation
    _segmentsTable['R'] = 0x0C;   // same as P
    _segmentsTable['S'] = 0x12;   // same as '5'
    _segmentsTable['T'] = 0x0F;
    _segmentsTable['U'] = 0x41;
    _segmentsTable['Y'] = 0x19;   // same as '4'
    _segmentsTable['Z'] = 0x24;   // same as '2'

    _segmentsTable['a'] = 0x20;
    _segmentsTable['b'] = 0x03;
    _segmentsTable['c'] = 0x26;
    _segmentsTable['d'] = 0x21;
    _segmentsTable['e'] = 0x06;
    _segmentsTable['f'] = 0x0E;
    _segmentsTable['h'] = 0x0B;
    _segmentsTable['i'] = 0x4F;
    _segmentsTable['j'] = 0x71;
    _segmentsTable['l'] = 0x47;
    _segmentsTable['n'] = 0x0B;
    _segmentsTable['o'] = 0x40;
    _segmentsTable['p'] = 0x0C;
    _segmentsTable['q'] = 0x18;
    _segmentsTable['r'] = 0x0C;
    _segmentsTable['t'] = 0x0F;
    _segmentsTable['u'] = 0x41;
    _segmentsTable['y'] = 0x19;
}
