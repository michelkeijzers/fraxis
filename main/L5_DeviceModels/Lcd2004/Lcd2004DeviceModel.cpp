#include "Lcd2004DeviceModel.hpp"
#include "../../L9_Utilities/Array/ArrayUtilities.hpp"
#include "../../L9_Utilities/String/StringUtilities.hpp"

Lcd2004DeviceModel::Lcd2004DeviceModel()
:   DeviceModel(), IDirty(), _previousLines { "" }, _lines { "" }, 
    _cursorPositionX(0), _cursorPositionY(0), _cursorEnabled(false), 
    _isCursorDirty(false)
{
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
}

const std::string_view Lcd2004DeviceModel::GetPreviousLine(uint8_t lineNumber) const
{
    return _previousLines[lineNumber];
}

const std::string_view Lcd2004DeviceModel::GetLine(uint8_t lineNumber) const
{
    return _lines[lineNumber];
}

void Lcd2004DeviceModel::SetLine(uint8_t lineNumber, std::string_view lineContent)
{
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
    return ArrayUtilities::FindFirstNonEqual(_previousLines, _lines, 4);
}

void Lcd2004DeviceModel::UpdateLine(uint8_t lineIndex)
{
    _previousLines[lineIndex] = _lines[lineIndex];
    if (GetDirtyLineNumber() == -1)
    {
        ClearDirty();
    }
}

bool Lcd2004DeviceModel::PerCharacterStrategy(uint8_t lineIndex) const
{
    uint8_t differentCharacters = StringUtilities::CountDifferentCharacters(_previousLines[lineIndex], _lines[lineIndex]);
    return (differentCharacters < FULL_LINE_STRATEGY_CHARACTERS); // See @details in class
}


