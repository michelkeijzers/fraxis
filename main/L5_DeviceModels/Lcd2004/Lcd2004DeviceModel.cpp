#include "Lcd2004DeviceModel.hpp"
#include "../../L4_DomainModels/I2c/Displays/Lcd2004/Lcd2004.hpp"
#include "../../L9_Utilities/Array/ArrayUtilities.hpp"
#include "../../L9_Utilities/String/StringUtilities.hpp"
#include "../../L9_Utilities/Assert/Assert.hpp"
#include <cstdint>

Lcd2004DeviceModel::Lcd2004DeviceModel()
:   DeviceModel(), _i2cAddress(0), 
    _cursorPositionX(0), _cursorPositionY(0), _cursorEnabled(false), 
    _isCursorDirty(false)
{
    for (uint8_t lineIndex = 0; lineIndex < 4; lineIndex++)
    {
        _previousLines[lineIndex] = std::string(Lcd2004::LINE_WIDTH, ' ');
        _lines[lineIndex]         = std::string(Lcd2004::LINE_WIDTH, ' ');
    }
}

Lcd2004DeviceModel::~Lcd2004DeviceModel()
{
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

const std::string_view Lcd2004DeviceModel::GetPreviousLine(uint8_t lineNumber) const
{
    Assert::IsTrue(IsInitialized());
    return _previousLines[lineNumber];
}

const std::string_view Lcd2004DeviceModel::GetLine(uint8_t lineNumber) const
{
    Assert::IsTrue(IsInitialized());
    return _lines[lineNumber];
}

void Lcd2004DeviceModel::SetLine(uint8_t lineNumber, std::string_view lineContent)
{
    Assert::IsTrue(IsInitialized());
    if (_lines[lineNumber] == lineContent) 
    {
        return;
    }
    _lines[lineNumber] = lineContent;
    MarkDirty();
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
    return ArrayUtilities::FindFirstNonEqual(_previousLines, _lines, 4);
}

void Lcd2004DeviceModel::UpdateLine(uint8_t lineIndex)
{
    Assert::IsTrue(IsInitialized());
    _previousLines[lineIndex] = _lines[lineIndex];
    if (GetDirtyLineNumber() == -1)
    {
        ClearDirty();
    }
}

bool Lcd2004DeviceModel::PerCharacterStrategy(uint8_t lineIndex) const
{
    Assert::IsTrue(IsInitialized());
    uint8_t differentCharacters = StringUtilities::CountDifferentCharacters(_previousLines[lineIndex], _lines[lineIndex]);
    return (differentCharacters < FULL_LINE_STRATEGY_CHARACTERS); // See @details in class
}


