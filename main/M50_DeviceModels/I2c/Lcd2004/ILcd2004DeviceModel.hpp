#pragma once

#include "../../../M40_DomainModels/I2c/Lcd2004/Lcd2004.hpp"
#include <cstdint>
#include <string>
#include <array>

namespace M50::I2c
{
    class ILcd2004DeviceModel;
}

namespace M90
{
    namespace Assert
    {
        class IAssert;
    }

    namespace Log
    {
        class ILog;
    }

    namespace Container
    {
        class IContainerUtilities;
    }

    namespace StringUtilities
    {
        class IStringUtilities;
    }
}

namespace M50::I2c
{
    class ILcd2004DeviceModel
    {
    public:
        static constexpr uint8_t NUMBER_OF_LINES = 4;

        virtual ~ILcd2004DeviceModel() = default;

        [[nodiscard]] virtual uint8_t GetI2cAddress() const = 0;

        virtual void SetI2cAddress(
            uint8_t i2cAddress) = 0;

        [[nodiscard]] virtual bool IsPredefinedCharacter(
            uint8_t slotIndex) const = 0;

        [[nodiscard]] virtual uint8_t GetPredefinedCharacterIndex(
            uint8_t slotIndex) const = 0;

        [[nodiscard]] virtual uint8_t GetCustomCharacterData(
            uint8_t slotIndex,
            uint8_t rowIndex) const = 0;

        void virtual SetPredefinedCharacterIndex(
            uint8_t slotIndex,
            uint8_t predefinedCharacterIndex) = 0;

        void virtual SetCustomCharacterData(
            uint8_t slotIndex,
            std::array<uint8_t, Lcd2004::CUSTOM_CHARACTER_DATA_LENGTH> data) = 0;

        [[nodiscard]] virtual std::string_view GetPreviousLine(
            uint8_t lineNumber) const = 0;

        [[nodiscard]] virtual std::string_view GetLine(
            uint8_t lineNumber) const = 0;

        void virtual SetLine(
            uint8_t lineNumber,
            std::string_view lineContent) = 0;

        [[nodiscard]] virtual bool IsCharacterDirty(uint8_t slotIndex) const = 0;
        
        virtual void ClearCharacterDirty(uint8_t slotIndex) = 0;

        [[nodiscard]] virtual bool IsCursorDirty() const = 0;
        
        virtual void ClearCursorDirty() = 0;

        [[nodiscard]] virtual int8_t GetDirtyLineNumber() const = 0;

        virtual void UpdateLine(
            uint8_t lineIndex) = 0;

        [[nodiscard]] virtual bool PerCharacterStrategy(
            uint8_t lineIndex) const = 0;
    };
}
