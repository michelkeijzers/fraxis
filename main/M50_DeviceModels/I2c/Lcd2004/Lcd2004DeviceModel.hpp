#pragma once

#include "ILcd2004DeviceModel.hpp"
#include "../../DeviceModel.hpp"
#include "../../../M40_DomainModels/I2c/Lcd2004/Lcd2004.hpp"
#include "../../../M60_DeviceDrivers/I2c/Lcd2004/ILcd2004DeviceDriver.hpp"


/// @class Lcd2004DeviceModel 
/// @brief  LCD 2004 device model class
/// @details
/// Because writing four lines takes quite some time, some design decisions are made:
/// First check the times needed for actions:
/// - Setting, enabling or disabling cursor: +/-            0.15       ms
/// - Clearing screen/returning home:                       1.7        ms
/// - Writing one character:                                0.16 - 0.2 ms 
/// - Writing 20 characters (consecutive):                  3.2  - 4.0 ms (excluding cursor 
///                                                                        repositioning)
/// - Writing 20 characters (nonconsecutive, same line):    6.2  - 7.0 ms (20 cursor repositionings)
///
/// The I2C bus speed is assumed to be 100 KHz (400 KHz is too much considering the long wires).
///
/// Conclusion 1: for four lines, it takes around 12.8-16.0 ms which is too much (assuming the 
/// MCP23017 needs to do its task every 10 ms at most). Thus writing all four lines in one Run is 
/// unacceptable.
///
/// Design decision 1: Only write one (dirty) line per Run. This means the dirty flag is kept per 
/// line. When a line is written, the dirty flag is reset for that line and the main dirty flag is
/// only reset after all four lines have been written. Doing other cursor commands can be done at 
/// will.
/// For this a separate dirty flag will be used.
///
/// To further optimize, there is a break even point when it is best to write a full line or per-
/// character.
/// The break even point is around 17 (although it depends on the regions). 
/// This is called FULL_LINE_STRATEGY_CHARACTERS.
/// To not fully overcomplicate, the following strategy is used:
///
/// Design decision 1: When a line differs 17 characters or more: write full line
/// Otherwise write per-character (iterate over chars, when gap: reposition cursor)

namespace M50::I2c
{

    class Lcd2004DeviceModel : public DeviceModel, public ILcd2004DeviceModel
    {
    public:
        // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
        Lcd2004DeviceModel(
            M90::Assert::IAssert& assert,
            M90::Log::ILog& log,
            M90::Container::IContainerUtilities& containerUtilities,
            M90::String::IStringUtilities& stringUtilities);

        Lcd2004DeviceModel(
            const Lcd2004DeviceModel&) = delete;

        Lcd2004DeviceModel& operator=(
            const Lcd2004DeviceModel&) = delete;

        Lcd2004DeviceModel(
            Lcd2004DeviceModel&&) = delete;

        Lcd2004DeviceModel& operator=(
            Lcd2004DeviceModel&&) = delete;

        // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
        ~Lcd2004DeviceModel() override;

        [[nodiscard]] uint8_t GetI2cAddress() const override;

        void SetI2cAddress(
            uint8_t i2cAddress) override;

        void Initialize() override;

        [[nodiscard]] bool IsPredefinedCharacter(
            uint8_t slotIndex) const override;

        [[nodiscard]] uint8_t GetPredefinedCharacterIndex(
            uint8_t slotIndex) const override;

        [[nodiscard]] uint8_t GetCustomCharacterData(
            uint8_t slotIndex,
            uint8_t rowIndex) const override;

        void SetPredefinedCharacterIndex(
            uint8_t slotIndex,
            uint8_t predefinedCharacterIndex) override;

        void SetCustomCharacterData(
            uint8_t slotIndex,
            std::array<uint8_t, Lcd2004::CUSTOM_CHARACTER_DATA_LENGTH> data) override;

        [[nodiscard]] std::string_view GetPreviousLine(
            uint8_t lineNumber) const override;

        [[nodiscard]] std::string_view GetLine(
            uint8_t lineNumber) const override;

        void SetLine(
            uint8_t lineNumber,
            std::string_view lineContent) override;

        [[nodiscard]] bool IsCharacterDirty(uint8_t slotIndex) const override;

        void ClearCharacterDirty(uint8_t slotIndex) override;

        [[nodiscard]] bool IsCursorDirty() const override;
        
        void ClearCursorDirty() override;

        [[nodiscard]] int8_t GetDirtyLineNumber() const override;

        void UpdateLine(
            uint8_t lineIndex) override;

        [[nodiscard]] bool PerCharacterStrategy(
            uint8_t lineIndex) const override;

    private:
        static constexpr uint8_t FULL_LINE_STRATEGY_CHARACTERS = 17; // See @details above
        uint8_t _i2cAddress;

        std::array<std::string, NUMBER_OF_LINES> _previousLines;

        std::array<std::string, NUMBER_OF_LINES> _lines;

        uint8_t _cursorPositionX;

        uint8_t _cursorPositionY;

        bool _cursorEnabled;

        /// @brief if true, _predefinedCharacterIndices[x] holds the index, otherwise 
        /// _customCharacterData holds the data.
        std::array<bool, M60::I2c::LCD2004_NUMBER_OF_CUSTOM_CHARACTERS>
            _isPredefinedCharacter;

        std::array<std::array<
            uint8_t, M60::I2c::LCD2004_CUSTOM_CHARACTER_DATA_LENGTH>,
            M60::I2c::LCD2004_NUMBER_OF_CUSTOM_CHARACTERS>
            _customCharacterData;

        std::array<uint8_t, M60::I2c::LCD2004_NUMBER_OF_CUSTOM_CHARACTERS>
            _predefinedCharacterIndices;

        std::array<bool, M60::I2c::LCD2004_NUMBER_OF_CUSTOM_CHARACTERS>
            _isCharacterDirty;

        bool _isCursorDirty; /// Or any other trivial command

        M90::Container::IContainerUtilities& _containerUtilities;
    };
}
