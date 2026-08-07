#include "Lcd2004DeviceModel.hpp"
#include "../../L4_DomainModels/I2c/Displays/Lcd2004/Lcd2004.hpp"
#include "../../L9_Utilities/Array/ArrayUtilities.hpp"
#include "../../L9_Utilities/String/StringUtilities.hpp"
#include "../../L9_Utilities/Assert/Assert.hpp"
#include <cstdint>

Lcd2004DeviceModel::Lcd2004DeviceModel()
:   DeviceModel(), 
    _i2cAddress(0), 
    _isCharacterDirty({}),
	_isPredefinedCharacter({}),
	_customCharacterData({}),
	_predefinedCharacterIndices({}),
    _cursorPositionX(0),
    _cursorPositionY(0),
    _cursorEnabled(false), 
    _isCursorDirty(false)
{
    for (uint8_t lineIndex = 0; lineIndex < 4; lineIndex++)
    {
        _previousLines[lineIndex] = std::string(Lcd2004::LINE_WIDTH, ' ');
        _lines[lineIndex]         = std::string(Lcd2004::LINE_WIDTH, ' ');
    }
}

uint8_t Lcd2004DeviceModel::GetI2cAddress() const
{
    return _i2cAddress;
}

void Lcd2004DeviceModel::SetI2cAddress(uint8_t i2cAddress)
{
    _i2cAddress = i2cAddress;
}

void Lcd2004DeviceModel::Initialize()
{
    MarkInitialized();
}

bool Lcd2004DeviceModel::IsPredefinedCharacter(
    uint8_t slotIndex) const
{
    return _isPredefinedCharacter[slotIndex];
}

uint8_t Lcd2004DeviceModel::GetPredefinedCharacterIndex(
    uint8_t slotIndex) const
{
    return _predefinedCharacterIndices[slotIndex];
}

uint8_t Lcd2004DeviceModel::GetCustomCharacterData(
    uint8_t slotIndex,
    uint8_t rowIndex) const
{
    return _customCharacterData[slotIndex][rowIndex];
}

void Lcd2004DeviceModel::SetPredefinedCharacterIndex(
    uint8_t slotIndex,
    uint8_t predefinedCharacterIndex)
{
    _isPredefinedCharacter[slotIndex] = true;
    _predefinedCharacterIndices[slotIndex] = predefinedCharacterIndex;
    _isCharacterDirty[slotIndex] = true;
    MarkDirty();
}

void Lcd2004DeviceModel::SetCustomCharacterData(
    uint8_t slotIndex,
    const uint8_t data[Lcd2004DeviceDriver::CUSTOM_CHARACTER_DATA_LENGTH])
{
    _isPredefinedCharacter[slotIndex] = false; // Custom character
    for (uint8_t index = 0; index < Lcd2004DeviceDriver::CUSTOM_CHARACTER_DATA_LENGTH; index++)
    {
        _customCharacterData[slotIndex][index] = data[index];
    }
    _isCharacterDirty[slotIndex] = true;
    MarkDirty();
}

std::string_view Lcd2004DeviceModel::GetPreviousLine(
    uint8_t lineNumber) const
{
    Assert::IsTrue(IsInitialized());
    return _previousLines[lineNumber];
}

std::string_view Lcd2004DeviceModel::GetLine(
    uint8_t lineNumber) const
{
    Assert::IsTrue(IsInitialized());
    return _lines[lineNumber];
}

void Lcd2004DeviceModel::SetLine(
    uint8_t lineNumber, std::string_view lineContent)
{
    Assert::IsTrue(IsInitialized());
    if (_lines[lineNumber] == lineContent) 
    {
        return;
    }
    _lines[lineNumber] = lineContent;
    MarkDirty();
}

bool Lcd2004DeviceModel::IsCharacterDirty(
    uint8_t slotIndex) const
{
    return _isCharacterDirty[slotIndex];
}

void Lcd2004DeviceModel::ClearCharacterDirty(
    uint8_t slotIndex)
{
    _isCharacterDirty[slotIndex] = false;
}

bool Lcd2004DeviceModel::IsCursorDirty() const
{
    return _isCursorDirty;
}

void Lcd2004DeviceModel::ClearCursorDirty()
{
    _isCursorDirty = false;
}

int8_t Lcd2004DeviceModel::GetDirtyLineNumber() const
{
    Assert::IsTrue(IsInitialized());
    return (uint8_t) ArrayUtilities::FindFirstNonEqual(_previousLines, _lines);
}

void Lcd2004DeviceModel::UpdateLine(
    uint8_t lineIndex)
{
    Assert::IsTrue(IsInitialized());
    _previousLines[lineIndex] = _lines[lineIndex];
    if (GetDirtyLineNumber() == -1)
    {
        ClearDirty();
    }
}

bool Lcd2004DeviceModel::PerCharacterStrategy(
    uint8_t lineIndex) const
{
    Assert::IsTrue(IsInitialized());
    auto differentCharacters = (uint8_t) StringUtilities::CountDifferentCharacters(
        _previousLines[lineIndex], _lines[lineIndex]);
    return (differentCharacters < FULL_LINE_STRATEGY_CHARACTERS); // See @details in class
}
