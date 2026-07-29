#pragma once

#include "../DeviceModel.hpp"
#include "../../L9_Utilities/Dirty/IDirty.hpp"
#include <cstdint>

class Tm1637DeviceModel : public DeviceModel, public IDirty
{
public:
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

    bool GetDirtyCharacter(uint8_t index);
    bool GetDirtyAuxiliarySegment(uint8_t index);
    /// @brief Clears all dirty flags.
    void ClearDirty() override;

private:
    /// @brief Number of digits used in _digits.
    uint8_t _nrOfDigits;

    /// @brief Only the most significant digits are used.
    char _characters[8];
    bool _dirtyCharacters[8];

    /// @brief Only the most significant segments are used.
    bool _auxiliarySegments[8];
    bool _dirtyAuxiliarySegments[8];
};
