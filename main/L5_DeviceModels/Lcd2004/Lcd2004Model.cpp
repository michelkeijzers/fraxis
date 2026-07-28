#include "Lcd2004Model.hpp"
#include "../../L9_Utilities/Array/ArrayUtilities.hpp"
#include "../../L9_Utilities/String/StringUtilities.hpp"

Lcd2004Model::Lcd2004Model()
:   DeviceModel(), IDirty(), _previousLines { "" }, _lines { "" }, 
    _cursorPositionX(0), _cursorPositionY(0), _cursorEnabled(false), 
    _isCursorDirty(false)
{
}

Lcd2004Model::~Lcd2004Model()
{
}

uint8_t Lcd2004Model::GetI2cAddress() const
{
    return _i2cAddress;
}

void Lcd2004Model::SetI2cAddress(uint8_t i2cAddress)
{
    _i2cAddress = i2cAddress;
}

void Lcd2004Model::Initialize()
{
}

const std::string Lcd2004Model::GetPreviousLine(uint8_t lineNumber) const
{
    return _previousLines[lineNumber];
}

const std::string Lcd2004Model::GetLine(uint8_t lineNumber) const
{
    return _lines[lineNumber];
}

void Lcd2004Model::SetLine(uint8_t lineNumber, std::string lineContent)
{
    if (_lines[lineNumber] == lineContent) 
    {
        return;
    }
    _lines[lineNumber] = lineContent;
    MarkDirty();
}


bool Lcd2004Model::IsCursorDirty() const
{
    return _isCursorDirty;
}

void Lcd2004Model::ClearCursorDirty()
{
    _isCursorDirty = false;
}

int8_t Lcd2004Model::GetDirtyLineNumber() const
{
    return ArrayUtilities::FindFirstNonEqual(_previousLines, _lines, 4);
}

void Lcd2004Model::UpdateLine(uint8_t lineIndex)
{
    _previousLines[lineIndex] = _lines[lineIndex];
    if (GetDirtyLineNumber() == -1)
    {
        ClearDirty();
    }
}

bool Lcd2004Model::PerCharacterStrategy(uint8_t lineIndex) const
{
    uint8_t differentCharacters = StringUtilities::CountDifferentCharacters(_previousLines[lineIndex], _lines[lineIndex]);
    return (differentCharacters < FULL_LINE_STRATEGY_CHARACTERS); // See @details in class
}


