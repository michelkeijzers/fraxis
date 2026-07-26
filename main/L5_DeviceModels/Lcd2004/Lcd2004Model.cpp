#include "Lcd2004Model.hpp"
#include "../DeviceSettings.hpp"
#include "../../L9_Utils/Array/ArrayUtils.hpp"
#include "../../L9_Utils/String/StringUtils.hpp"

Lcd2004Model::Lcd2004Model()
:   DeviceModel(), IDirty(), _i2cModel(nullptr), _previousLines { "" }, _lines { "" }, 
    _cursorPositionX(0), _cursorPositionY(0), _cursorEnabled(false), 
    _isCursorDirty(false)
{
}

Lcd2004Model::~Lcd2004Model()
{
}

void Lcd2004Model::SetI2cModel(I2cModel& i2cModel)
{
    _i2cModel = &i2cModel;
}

void Lcd2004Model::Initialize()
{
    _i2cAddress = DeviceSettings::I2C_ADDRESS_LCD2004;
}

void Lcd2004Model::WriteLine(uint8_t line, std::string lineContent)
{
    if (_lines[line] == lineContent) 
    {
        return;
    }
    _lines[line] = lineContent;
    MarkDirty();
}

/// @note See class description
void Lcd2004Model::WriteToDriver()
{
    if (_isCursorDirty)
    {
        // TODO Write cursor
        _isCursorDirty = false;
    }

    int8_t dirtyLineIndex = ArrayUtils::FindFirstNonEqual(_previousLines, _lines, 4);
    if (dirtyLineIndex != -1)
    {
        //TODO WriteLineToDriver(dirtyLineIndex);
        if (ArrayUtils::FindFirstNonEqual(_previousLines, _lines, 4) != -1)
        {
            ClearDirty();
        }
    }
}

// void Lcd2004Model::WriteLineToDriver(uint8_t lineIndex)
// {
//     //TODO: Write to driver
//     uint8_t differentCharacters = StringUtils::CountDifferentCharacters(_previousLines[lineIndex], _lines[lineIndex]);
//     if (differentCharacters >= FULL_LINE_STRATEGY_CHARACTERS) // See @details in class
//     {
//         WriteFullLineToDriver(lineIndex);
//     }
//     else
//     {
//         WriteDifferentCharactersToDriver(lineIndex);
//     }

//     //var differentCharacters = 
//     _previousLines[lineIndex] = _lines[lineIndex];
// }

// void Lcd2004Model::WriteFullLineToDriver(uint8_t lineIndex)
// {
//     // TODO: Write full line (context needed, only LCD2004 device driver)
// }

// void Lcd2004Model::WriteDifferentCharactersToDriver(uint8_t lineIndex)
// {
//     std::string& previousLine = _previousLines[lineIndex];
//     std::string& line = _lines[lineIndex];

//     int8_t cursorPosition = -1;
//     for (uint8_t index = 0; index < line.length(); index++)
//     {
//         if (previousLine[index] != line[index]) 
//         {
//             if (cursorPosition != index)
//             {
//                 //TODO: Set cursor position to index (do not call above as it removes dirtycursor) 
//                 cursorPosition = index;
//             }
//             //TODO: Write char
//             cursorPosition++;
//         }
//     }
// }
