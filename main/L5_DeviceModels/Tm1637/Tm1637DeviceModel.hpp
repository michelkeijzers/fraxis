#pragma once

#include "../DeviceModel.hpp"
#include <cstdint>

class Tm1637DeviceModel : public DeviceModel
{
public:
    static const uint8_t MAX_NR_OF_DIGITS = 8;

    /// @brief Special symbols which are not within ASCII range.
    enum class ESymbol
    {
        Degrees = 0x80
    };

    /// @brief Brightness of segments.
    /// @todo: Future: Make brightness flexible
    static const uint8_t BRIGHTNESS = 0x07;

    Tm1637DeviceModel();
    ~Tm1637DeviceModel();

    uint8_t GetNrOfDigits();
    void SetNrOfDigits(uint8_t nrOfDigits);
    void Initialize() override;

    uint8_t GetDigit(uint8_t index);
    void SetDigit(uint8_t index, uint8_t value);
    char GetCharacter(uint8_t index);
    void SetCharacter(uint8_t index, char character);
    bool GetAuxiliarySegment(uint8_t index);
    void SetAuxiliarySegment(uint8_t index, bool state);

    uint8_t GetSegmentsValue(uint8_t index);

    bool IsCharacterDirty(uint8_t index);

    /// @brief Clears all dirty flags.
    void ClearDirty() override;

private:
    /// @todo: place in a different file, not store for each TM1637 instance.
    uint8_t _segmentsTable[256];

    /// @brief Number of digits used in _digits.
    uint8_t _nrOfDigits;

    /// @brief Only the most significant digits are used.
    char _characters[MAX_NR_OF_DIGITS];
    bool _dirtyCharacters[MAX_NR_OF_DIGITS];

    /// @brief Only the most significant segments are used.
    bool _auxiliarySegments[MAX_NR_OF_DIGITS];

    void FillSegmentsTable();
};
