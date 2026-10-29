#pragma once

#include "../DeviceModel.hpp"
#include <cstdint>
#include <array>

class Tm1637DeviceModel : public DeviceModel
{
public:
    static const uint8_t MAX_NR_OF_DIGITS = 8;
    static const uint16_t NR_OF_SYMBOLS = 256;

    /// @brief Special symbols which are not within ASCII range.
    enum class ESymbol : uint8_t
    {
        Degrees = 0x80
    };

    /// @brief Brightness of segments.

    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    Tm1637DeviceModel();

    Tm1637DeviceModel(const Tm1637DeviceModel&) = delete;
    Tm1637DeviceModel& operator=(const Tm1637DeviceModel&) = delete;
    Tm1637DeviceModel(Tm1637DeviceModel&&) = delete;
    Tm1637DeviceModel& operator=(Tm1637DeviceModel&&) = delete;

    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    ~Tm1637DeviceModel() override;

    [[nodiscard]] bool IsEnabled() const;
    void Enable(
        bool enable);

    [[nodiscard]] uint8_t GetBrightness() const;
    void SetBrightness(
        uint8_t brightness);

    [[nodiscard]] uint8_t GetNrOfDigits();
    void SetNrOfDigits(
        uint8_t nrOfDigits);
    void Initialize() override;

    [[nodiscard]] uint8_t GetDigit(
        uint8_t index);
    void SetDigit(
        uint8_t index, 
        uint8_t value);
    [[nodiscard]] char GetCharacter(
        uint8_t index);
    void SetCharacter(
        uint8_t index, char character);
    [[nodiscard]] bool GetAuxiliarySegment(
        uint8_t index);
    void SetAuxiliarySegment(
        uint8_t index, bool state);

    [[nodiscard]] uint8_t GetSegmentsValue(
        uint8_t index);

    [[nodiscard]] bool IsCharacterDirty(
        uint8_t index);

    /// @brief Clears all dirty flags.
    void ClearDirty() override;

private:
    bool _isEnabled;

    uint8_t _brightness;

    /// @todo: place in a different file, not store for each TM1637 instance.
    std::array<uint8_t, NR_OF_SYMBOLS> _segmentsTable;

    /// @brief Number of digits used in _digits.
    uint8_t _nrOfDigits;

    /// @brief Only the most significant digits are used.
    std::array<char, MAX_NR_OF_DIGITS> _characters;
    std::array<bool, MAX_NR_OF_DIGITS> _digits;

    std::array<bool, MAX_NR_OF_DIGITS> _auxiliarySegments;

    /// @brief Only the most significant segments are used.
    std::array<bool, MAX_NR_OF_DIGITS> _dirtyCharacters;

    void FillSegmentsTable();
};
