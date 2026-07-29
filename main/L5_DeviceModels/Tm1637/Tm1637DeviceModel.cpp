#include "Tm1637DeviceModel.hpp"
#include "../../L9_Utilities/Assert/Assert.hpp"

Tm1637DeviceModel::Tm1637DeviceModel()
{
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
}

uint8_t Tm1637DeviceModel::GetDigit(uint8_t index)
{
    Assert::IsTrue(index < _nrOfDigits, "index");
    return uint8_t(_characters[index] - '0');
}

void Tm1637DeviceModel::SetDigit(uint8_t index, uint8_t value)
{
    Assert::IsTrue(index < _nrOfDigits, "index");
    Assert::IsBetween(value, 0, 10, "value");
    uint8_t newCharacter = '0' + value;
    if (_characters[index] != newCharacter)
    {
        _characters[index] = newCharacter;
        MarkDirty();
    }
}

char Tm1637DeviceModel::GetCharacter(uint8_t index)
{
    Assert::IsTrue(index < _nrOfDigits, "index");
    return _characters[index];
}

void Tm1637DeviceModel::SetCharacter(uint8_t index, char character)
{
    Assert::IsTrue(index < _nrOfDigits, "index");
    if (_characters[index] != character)
    {
        _characters[index] = character;
        MarkDirty();
    }
    _characters[index] = character;
}

bool Tm1637DeviceModel::GetAuxiliarySegment(uint8_t index)
{
    Assert::IsTrue(index < _nrOfDigits, "index");
    return _auxiliarySegments[index];
}

void Tm1637DeviceModel::SetAuxiliarySegment(uint8_t index, bool state)
{
    Assert::IsTrue(index < _nrOfDigits, "index");
    if (_auxiliarySegments[index] != state)
    {
        _auxiliarySegments[index] = state;
        MarkDirty();
    }
}

bool Tm1637DeviceModel::GetDirtyCharacter(uint8_t index)
{
    Assert::IsTrue(index < _nrOfDigits, "index");
    return _dirtyCharacters[index];
}

bool Tm1637DeviceModel::GetDirtyAuxiliarySegment(uint8_t index)
{
    Assert::IsTrue(index < _nrOfDigits, "index");
    return _dirtyAuxiliarySegments[index];
}

void Tm1637DeviceModel::ClearDirty()
{
    for (uint8_t index = 0; index < _nrOfDigits; index++)
    {
        _dirtyCharacters[index] = false;
        _dirtyAuxiliarySegments[index] = false;
    }
    IDirty::ClearDirty();
}
