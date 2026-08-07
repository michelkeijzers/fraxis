#pragma once

#include "../../L6_DeviceDrivers/Lcd2004/Lcd2004DeviceDriver.hpp"
#include "../DeviceModel.hpp"
#include <cstdint>
#include <string>
#include <array>

/// @class Lcd2004DeviceModel 
/// @brief  LCD 2004 device model class
/// @details
/// Because writing four lines takes quite some time, some design decisions are made:
/// First check the times needed for actions:
/// - Setting, enabling or disabling cursor: +/-            0.15       ms
/// - Clearing screen/returning home:                       1.7        ms
/// - Writing one character:                                0.16 - 0.2 ms 
/// - Writing 20 characters (consecutive):                  3.2  - 4.0 ms (excluding cursor repositioning)
/// - Writing 20 characters (nonconsecutive, same line):    6.2  - 7.0 ms (20 cursor repositionings)
///
/// The I2C bus speed is assumed to be 100 KHz (400 KHz is too much considering the long wires).
///
/// Conclusion 1: for four lines, it takes around 12.8-16.0 ms which is too much (assuming the MCP23017 needs to 
/// do its task every 10 ms at most). Thus writing all four lines in one Run is unacceptable.
///
/// Design decision 1: Only write one (dirty) line per Run. This means the dirty flag is kept per line and the main 
/// dirty flag is only reset after all four lines have been written. Doing other cursor commands can be done at will.
/// For this a separate dirty flag will be used.
///
/// To further optimize, there is a break even point when it is best to write a full line or per-character.
/// The break even point is around 17 (although it depends on the regions). 
/// This is called FULL_LINE_STRATEGY_CHARACTERS.
/// To not fully overcomplicate, the following strategy is used:
///
/// Design decision 1: When a line differs 17 characters or more: write full line
/// Otherwise write per-character (iterate over chars, when gap: reposition cursor)

class Lcd2004DeviceModel : public DeviceModel
{
public:
    static constexpr uint8_t NUMBER_OF_LINES = 4;

    Lcd2004DeviceModel();
    ~Lcd2004DeviceModel() = default;

    uint8_t GetI2cAddress() const;
    void SetI2cAddress(
        uint8_t i2cAddress);

    void Initialize() override;

    bool IsPredefinedCharacter(
        uint8_t slotIndex) const;
    uint8_t GetPredefinedCharacterIndex(
        uint8_t slotIndex) const;
    uint8_t GetCustomCharacterData(
        uint8_t slotIndex,
        uint8_t rowIndex) const;
    void SetPredefinedCharacterIndex(
        uint8_t slotIndex,
        uint8_t predefinedCharacterIndex);
    void SetCustomCharacterData(
        uint8_t slotIndex,
        const uint8_t data[Lcd2004DeviceDriver::CUSTOM_CHARACTER_DATA_LENGTH]);

    std::string_view GetPreviousLine(
        uint8_t lineNumber) const;
    std::string_view GetLine(
        uint8_t lineNumber) const;
    
    void SetLine(
        uint8_t lineNumber,
        std::string_view lineContent);

    bool IsCharacterDirty(uint8_t slotIndex) const;
    void ClearCharacterDirty(uint8_t slotIndex) ;

    bool IsCursorDirty() const;
    void ClearCursorDirty();

    int8_t GetDirtyLineNumber() const;
    void UpdateLine(
        uint8_t lineIndex);
    bool PerCharacterStrategy(
        uint8_t lineIndex) const;

private:
    static constexpr uint8_t FULL_LINE_STRATEGY_CHARACTERS = 17; // See @details above
    uint8_t _i2cAddress;

    std::array<std::string, NUMBER_OF_LINES> _previousLines;
    std::array<std::string, NUMBER_OF_LINES> _lines;
    uint8_t _cursorPositionX;
    uint8_t _cursorPositionY;  
    bool _cursorEnabled;

    /// @brief if true, _predefinedCharacterIndices[x] holds the index, otherwise 
    /// _customeCharacterData holds the data.
    std::array<bool, Lcd2004DeviceDriver::NUMBER_OF_CUSTOM_CHARACTERS> _isPredefinedCharacter;
    std::array<std::array<uint8_t, Lcd2004DeviceDriver::CUSTOM_CHARACTER_DATA_LENGTH>,
                        Lcd2004DeviceDriver::NUMBER_OF_CUSTOM_CHARACTERS> _customCharacterData;
    std::array<uint8_t, Lcd2004DeviceDriver::NUMBER_OF_CUSTOM_CHARACTERS> _predefinedCharacterIndices;

    std::array<bool, Lcd2004DeviceDriver::NUMBER_OF_CUSTOM_CHARACTERS> _isCharacterDirty;
    bool _isCursorDirty; /// Or any other trivial command
};
